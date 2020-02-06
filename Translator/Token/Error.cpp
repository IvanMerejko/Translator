#include "Error.h"
#include <fstream>

Error::Error (const Context& context)
    :BaseElement{context}
{}
Symbol Error::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol nextSymbol{};
    file.get(nextSymbol);
    ++column;
    return nextSymbol;
}
OptionalSymbolsString Error::GetParsedElementInString() const noexcept
{
    return std::nullopt;
}
ParsingState Error::GetElementParsingState() const noexcept
{
    return ParsingState::Normal;
}