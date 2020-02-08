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

    TokenNumber AddNewIdentifier(TokenView name, TokenNameToCodeMap& identifiers);
    TokenNumber AddNewConstant(TokenView name, TokenNameToCodeMap& constants);

    Categories GetSymbolCategories(Symbol symbol, const Context& context);

    constexpr auto incrementLineIfNeed(Symbol symbol, TokenLine& line, TokenColumn& column)
    {
        if (symbol == '\n' || symbol=='\r')
        {
            ++line;
            column = 1;
            return true;
        }
        return false;
    }
}



