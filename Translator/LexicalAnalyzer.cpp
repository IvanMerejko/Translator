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
#include <memory>

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
        const auto symbolCategory = GetSymbolCategories(currentSymbol, m_context);
        if(symbolCategory == Categories::StartComment)
        {
            auto isNotCommentStartSecondSymbol = specialCaseForCommentStart(file);
            if( isNotCommentStartSecondSymbol )
            {
                currentSymbol = *isNotCommentStartSecondSymbol;
                continue;
            }
        }
        const auto tokenPointer = getElementPointer(currentSymbol, symbolCategory);
        currentSymbol = tokenPointer->ParseElement(file, line, endTokenPosition);
        const auto parseToken = tokenPointer->GetParsedElementInString();
        if(parseToken)
        {
            std::cout << *parseToken << "   " << line << "  " << startTokenPosition <<'\n';

        }
        startTokenPosition = endTokenPosition - 1;
    }
}

UpElement LexicalAnalyzer::getElementPointer(Symbol currentSymbol,Categories category) const
{
    switch (category)
    {
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