#pragma once
#include <map>
#include <optional>
#include <memory>
#include <vector>

enum class Categories
{
    WhiteSpace               = 0,
    StartConstant            = 1,
    StartIdentifier          = 2,
    OneSymbolSeparator       = 3,
    StartComment             = 5,
    ErrorSymbol              = 6,
    SharpStart               = 7,
    ScipSymbol               = 100, ///special ca
/// Use for \r
};
enum class ParsingState
{
    Normal = 0,
    ErrorUnclosedComment = 1,
    ErrorIncorrectSymbol = 2,
    ErrorIncorrectSymbolAfterIdentifier = 3,
    ErrorIncorrectSymbolAfterConstant = 4,
    ErrorInParsingSharpTextMustBeLetter = 5,
    ErrorInParsingSharpTextMustBePlus = 6,
    ErrorInParsingSharpTextMustBeDigit = 7,
    ErrorInParsingSharpTextMustBeStar = 8,
};
using Code = int;
using TokenName = std::string;
using SymbolsString = std::string;
using SymbolsCategories = std::map<Code, Categories>;
using TokenNameToCodeMap = std::map<TokenName, Code>;
using Symbol = char;
using OptionalSymbol = std::optional<char>;
using OptionalSymbolsString = std::optional<SymbolsString>;

using TokenNumber = unsigned int;
using TokenLine = unsigned int;
using TokenColumn = unsigned int;
using TokenInfo = std::tuple<TokenName, TokenNumber, TokenLine, TokenColumn>;
using TokensInfoVector = std::vector<TokenInfo>;
using TokenView = std::string_view;
using StringVector = std::vector<std::string>;

struct Info
{
    std::string m_name;
    TokenLine m_line;
    TokenColumn m_column;
};