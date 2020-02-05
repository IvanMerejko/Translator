#pragma once

#include "TypesFmd.h"

constexpr auto CharToInt(char value)
{
    return static_cast<int>(value);
}

SymbolsCategories CreateSymbolsCategories();

NameToCodeMap CreateIdentifiersMap();
