#pragma once

#include "TypesFmd.h"
#include "../Context.h"

namespace utils
{
    constexpr auto CharToInt(char value)
    {
        return static_cast<int>(value);
    }

    SymbolsCategories CreateSymbolsCategories();

    TokenNameToCodeMap CreateKeywordsMap();

    TokenNumber AddNewIdentifierIfNotExist(TokenView name, TokenNameToCodeMap& identifiers);
    TokenNumber AddNewConstantIfNotExist(TokenView name, TokenNameToCodeMap& constants);

    Categories GetSymbolCategories(Symbol symbol, const Context& context);

    constexpr auto incrementLineIfNeed(Symbol symbol, TokenLine& line, TokenColumn& column)
    {
        if (symbol == '\n')
        {
            ++line;
            column = 1;
            return true;
        }
        return false;
    }

    constexpr auto IsSpace(Symbol symbol)
    {
        return symbol == ' ' || symbol == '\n' || symbol == '\r';
    }
}



