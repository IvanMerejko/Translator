//
// Created by Ivan on 06.02.2020.
//

#include "OneSymbolSeparator.h"
#include <fstream>
OneSymbolSeparator::OneSymbolSeparator(Symbol separator, const Context& context)
    : BaseElement{context}
    , m_separator{separator}
{}
Symbol OneSymbolSeparator::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol currentSymbol{};
    file.get(currentSymbol);
    return currentSymbol;
}
OptionalSymbolsString OneSymbolSeparator::GetParsedElementInString() const noexcept
{
    return m_separator;
}
ParsingState OneSymbolSeparator::GetElementParsingState() const noexcept
{
    return ParsingState::Normal;
}