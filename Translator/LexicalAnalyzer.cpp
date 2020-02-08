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
#include <memory>
#include <string>
#include <algorithm>

void LexicalAnalyzer::StartAnalyze(std::string_view file_name)
{
    TokenLine line{1};
    TokenColumn startTokenPosition{1};
    TokenColumn endTokenPosition{1};
    std::ifstream file(file_name.data());
    if(!file.is_open())
    {
        std::cout << "Not found file\n";
        return;
    }
    Symbol currentSymbol{};
    file.get(currentSymbol);
    while(currentSymbol != EOF)
    {
        const auto symbolCategory = utils::GetSymbolCategories(currentSymbol, m_context);
        if(symbolCategory == Categories::StartComment)
        {
            auto isNotCommentStartSecondSymbol = specialCaseForCommentStart(file);
            if( isNotCommentStartSecondSymbol )
            {
                currentSymbol = *isNotCommentStartSecondSymbol;
                continue;
            }
        }
        const auto tokenPointer = getElementPointer(currentSymbol, symbolCategory, line, startTokenPosition);
        currentSymbol = tokenPointer->ParseElement(file, line, endTokenPosition);
        const auto parseToken = tokenPointer->GetParsedElementInString();
        if(parseToken)
        {
            m_tokensInfoVector.emplace_back(getTokenNumber(*parseToken, symbolCategory),
                    line, startTokenPosition);
        }
        startTokenPosition = endTokenPosition;
    }
}

UpElement LexicalAnalyzer::getElementPointer(Symbol currentSymbol,Categories category,
        TokenLine line, TokenColumn column)
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
            m_errors.emplace_back(createErrorStringOfIncorrectSymbol(currentSymbol, line, column));
            return std::make_unique<Error>(m_context);
    }
}

OptionalSymbol LexicalAnalyzer::specialCaseForCommentStart(std::ifstream& file) const
{
    Symbol nextSymbol{};
    file.get(nextSymbol);
    if(nextSymbol == EOF || nextSymbol != '<')
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
    return m_context.AddNewIdentifier(tmp);
}
TokenNumber LexicalAnalyzer::getOneSymbolSeparatorNumber(Symbol symbol) const noexcept
{
    return utils::CharToInt(symbol);
}

TokenNumber LexicalAnalyzer::getConstantNumber(const TokenName& name) noexcept
{
    return m_context.AddNewConstant(name);
}

void LexicalAnalyzer::PrintResult() const noexcept
{
    for(const auto& [tokenNumber, line, column] : m_tokensInfoVector)
    {
        std::cout << "TokenNumber : " << tokenNumber
                  << " line = " << line
                  << " column = " << column << '\n';
    }
    std::cout << "\n\n";
    for(const auto& errorText : m_errors)
    {
        std::cout << errorText << '\n';
    }
}
std::string LexicalAnalyzer::createErrorStringOfIncorrectSymbol(Symbol name, TokenLine line, TokenColumn column) const
{
    std::string text = LineString;
    text.append(std::to_string(line))
        .append(ColumnString)
        .append(std::to_string(column))
        .append(ErrorSymbol)
        .append(1, name);
    return text;
}