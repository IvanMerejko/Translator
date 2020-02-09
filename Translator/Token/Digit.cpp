#include "Digit.h"
#include "iostream"
#include <fstream>
#include "../Common/Utils.h"


Digit::Digit(Symbol startDigit, const Context& context)
    : BaseElement{context}
    , m_digit{startDigit}
{}
Symbol Digit::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol currentSymbol{};
    while ( file.get(currentSymbol))
    {
        ++column;
        if(utils::GetSymbolCategories(currentSymbol, m_context) != Categories::StartConstant)
        {
            if(!utils::IsSpace(currentSymbol))
            {
                m_parsingState = ParsingState::ErrorIncorrectSymbolAfterConstant;
            }
            return currentSymbol;
        }
        m_digit.append(1, currentSymbol);
    }
    return EOF;
}

OptionalSymbolsString Digit::GetParsedElementInString() const noexcept
{
    return m_digit;
}

ParsingState Digit::GetElementParsingState() const noexcept
{
    return ParsingState::Normal;
}