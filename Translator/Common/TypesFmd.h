#pragma once
#include<map>

enum class Categories
{
    WhiteSpace               = 0,
    StartConstant            = 1,
    StartIdentifier          = 2,
    OneSymbolSeparator        = 3,
    StartManySymbolSeparator = 4,
    StartComment             = 5,
    ErrorSymbol              = 6,
};
using Code = int;
using Name = std::string;
using SymbolsString = std::string;
using SymbolsCategories = std::map<Code, Categories>;
using NameToCodeMap = std::map<Name, Code>;
using Symbol = char;