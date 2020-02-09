#include "LexicalAnalyzer.h"
#include <type_traits>
#include <fstream>
#include "Common/TypesFmd.h"
#include "Common/Utils.h"
#include "Token/WhiteSpace.h"
#include "Token/Digit.h"
#include "Token/Identifier.h"
#include "Token/Comment.h"
#include "Token/OneSymbolSeparator.h"
#include "Token/Error.h"
#include "Common/Constants.h"
#include "Common/ErrorStringCreator.h"
#include <memory>
#include <string>
#include <algorithm>
#include <iomanip>

void LexicalAnalyzer::StartAnalyze(std::string_view file_name)
{
    TokenLine previousLine{1};
    TokenLine currentLine{1};
    TokenColumn startTokenPosition{1};
    TokenColumn endTokenPosition{1};
    std::ifstream file(file_name.data());
    if(!file.is_open())
    {
        std::cout << "Not found file\n";
        return;
    }
    Symbol currentSymbol{};
    Symbol nextSymbol{};
    file.get(currentSymbol);
    while(currentSymbol != EOF)
    {
        const auto symbolCategory = utils::GetSymbolCategories(currentSymbol, m_context);
        if(symbolCategory == Categories::StartComment)
        {
            auto isNotCommentStartSecondSymbol = specialCaseForCommentStart(file, endTokenPosition);
            if( isNotCommentStartSecondSymbol )
            {
                currentSymbol = *isNotCommentStartSecondSymbol;
                continue;
            }
        }
        const auto tokenPointer = getElementPointer(currentSymbol, symbolCategory);
        nextSymbol = tokenPointer->ParseElement(file, currentLine, endTokenPosition);
        const auto parsingState = tokenPointer->GetElementParsingState();
        if(auto errorString = isParsingStateNormal( parsingState,
                                                    currentSymbol,
                                                    nextSymbol,
                                                    previousLine,
                                                    startTokenPosition,
                                                    endTokenPosition);
            errorString)
        {
            m_errors.emplace_back(*errorString);
            break;
        }
        if(auto parseToken = tokenPointer->GetParsedElementInString();
            parseToken)
        {
            m_tokensInfoVector.emplace_back(*tokenPointer->GetParsedElementInString(),
                    getTokenNumber(*parseToken, symbolCategory),
                    currentLine,
                    startTokenPosition);
        }
        startTokenPosition = endTokenPosition;
        currentSymbol = nextSymbol;
        previousLine = currentLine;
    }
}

UpElement LexicalAnalyzer::getElementPointer(Symbol currentSymbol,Categories category)
{
    switch (category)
    {
        case Categories::ScipSymbol:
        case Categories::WhiteSpace:
            return std::make_unique<WhiteSpace>(m_context);
        case Categories::StartConstant:
            return std::make_unique<Digit>(currentSymbol, m_context);
        case Categories::StartIdentifier:
            return std::make_unique<Identifier>(currentSymbol, m_context);
        case Categories::StartComment:
            return std::make_unique<Comment>(m_context);
        case Categories::OneSymbolSeparator:
            return std::make_unique<OneSymbolSeparator>(currentSymbol, m_context);
        case Categories::ErrorSymbol:
            return std::make_unique<Error>(m_context);
    }
}

OptionalSymbol LexicalAnalyzer::specialCaseForCommentStart(std::ifstream& file, TokenLine& column) const
{
    Symbol nextSymbol{};
    file.get(nextSymbol);
    ++column;
    if(nextSymbol == EOF || nextSymbol != '*')
    {
        return nextSymbol;
    }
    return std::nullopt;
}

TokenNumber LexicalAnalyzer::getTokenNumber(const TokenName& name, Categories category) noexcept
{
    switch (category)
    {
        case Categories::OneSymbolSeparator:
            return getOneSymbolSeparatorNumber(name[0]);
        case Categories::StartIdentifier:
            return getIdentifierNumber(name);
        case Categories::StartConstant:
            return getConstantNumber(name);
        default:
            return 0;
    }
}

TokenNumber LexicalAnalyzer::getIdentifierNumber(const TokenName& name) noexcept
{
    const auto& keywords = m_context.GetKeywords();
    auto tmp = name;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), tolower);
    const auto it = keywords.find(tmp);
    if(it != keywords.end())
    {
        return it->second;
    }
    return m_context.AddNewIdentifierIfNotExist(tmp);
}
TokenNumber LexicalAnalyzer::getOneSymbolSeparatorNumber(Symbol symbol) const noexcept
{
    return utils::CharToInt(symbol);
}

TokenNumber LexicalAnalyzer::getConstantNumber(const TokenName& name) noexcept
{
    return m_context.AddNewConstantIfNotExist(name);
}

void LexicalAnalyzer::PrintResult() const noexcept
{
    for(const auto& [tokenName, tokenNumber, line, column] : m_tokensInfoVector)
    {
        std::cout << " TokenName : "   << std::setw(10) << std::left << tokenName
                  << " TokenNumber : " << std::setw(10) << std::left << tokenNumber
                  << " line = "        << std::setw(10) << std::left << line
                  << " column = "      << std::setw(10) << std::left << column << '\n';
    }
    std::cout << "\n\n";
    for(const auto& errorText : m_errors)
    {
        std::cout << errorText << '\n';
    }
}

OptionalSymbolsString LexicalAnalyzer::isParsingStateNormal(ParsingState state,  Symbol startSymbol,
    Symbol endSymbol, TokenLine line, TokenColumn columnStart, TokenColumn columnEnd)
{
    switch (state)
    {
        case ParsingState::Normal:
            return std::nullopt;
        case ParsingState::ErrorIncorrectSymbol:
            return ErrorStringCreator::createErrorStringOfIncorrectSymbol(startSymbol, line, columnStart);
        case ParsingState::ErrorUnclosedComment:
            return ErrorStringCreator::createErrorStringOfUnclosedComment(line, columnStart);
        case ParsingState::ErrorIncorrectSymbolAfterConstant:
            return ErrorStringCreator::createErrorStringOfIncorrectSymbolAfterConstant(endSymbol, line, columnEnd);
        case ParsingState::ErrorIncorrectSymbolAfterIdentifier:
            return ErrorStringCreator::createErrorStringOfIncorrectSymbolAfterIdentifier(endSymbol, line, columnEnd);
    }
}