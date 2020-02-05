#include "Digit.h"
#include "iostream"
#include <fstream>
#include "../Common/Utils.h"

Digit::Digit(Symbol startDigit, const Context& context)
    : BaseElement{context}
    , m_digit{startDigit}
{}
Symbol Digit::ParseElement(std::iostream& file)
{
    Symbol currentSymbol{};
    while ( file.get(currentSymbol))
    {
        if(GetSymbolCategories(currentSymbol, m_context) != Categories::StartConstant)
        {
            return currentSymbol;
        }
        m_digit.append(1, currentSymbol);
    }
    return EOF;
}

SymbolsString Digit::GetParsedElementInString() const noexcept
{
    return m_digit;
}