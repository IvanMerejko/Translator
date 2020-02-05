#pragma once

#include "TypesFmd.h"
#include "../Context.h"

constexpr auto CharToInt(char value)
{
    return static_cast<int>(value);
}

SymbolsCategories CreateSymbolsCategories();

NameToCodeMap CreateKeywordsMap();

Categories GetSymbolCategories(Symbol symbol, const Context& context);