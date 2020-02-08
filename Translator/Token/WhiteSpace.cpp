#include "WhiteSpace.h"
#include "BaseElement.h"
#include "../Context.h"
#include "../Common/TypesFmd.h"
#include "../Common/Utils.h"
#include <optional>
#include <fstream>
WhiteSpace::WhiteSpace(const Context& context)
    :BaseElement{context}
{}

Symbol WhiteSpace::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol currentSymbol{};
    utils::incrementLineIfNeed(currentSymbol, line, column);
    while ( file.get(currentSymbol))
    {
        ++column;
        const auto symbolCategory = utils::GetSymbolCategories(currentSymbol, m_context);
        if (symbolCategory == Categories::ScipSymbol)
        {
            continue;
        } else if( symbolCategory != Categories::WhiteSpace)
        {
            return currentSymbol;
        }
        if(utils::incrementLineIfNeed(currentSymbol, line, column))
        {
            column = 0;
        }
    }
    return EOF;
}
OptionalSymbolsString WhiteSpace::GetParsedElementInString() const noexcept
{
    return std::nullopt;
}

ParsingState WhiteSpace::GetElementParsingState() const noexcept
{
    return ParsingState::Normal;
}