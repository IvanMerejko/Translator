#pragma once
#include <map>
#include <optional>
#include <memory>

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
///using in Comment
enum class ParsingState
{
    Normal = 0,
    Error = 1
};
using Code = int;
using Name = std::string;
using SymbolsString = std::string;
using SymbolsCategories = std::map<Code, Categories>;
using NameToCodeMap = std::map<Name, Code>;
using Symbol = char;
using OptionalSymbol = std::optional<char>;
