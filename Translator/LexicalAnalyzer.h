#pragma once
#include <string_view>
//#include <filesystem>
//#include <string_view>
#include "Context.h"
#include "Token/BaseElement.h"

class LexicalAnalyzer
{
public:

public:
    LexicalAnalyzer() = default;
	void StartAnalyze(std::string_view file_name);
    void PrintResult() const noexcept ;
    const TokensInfoVector& GetTokensInfoVector() const noexcept ;
    const Context& GetContext() const noexcept ;
private:
    UpElement getElementPointer(Symbol currentSymbol, Categories category);
    OptionalSymbol specialCaseForCommentStart(std::ifstream& file, TokenLine& column) const;
    TokenNumber getTokenNumber(const TokenName& name, Categories category) noexcept ;
    TokenNumber getIdentifierNumber(const TokenName& name) noexcept ;
    TokenNumber getOneSymbolSeparatorNumber(Symbol symbol) const noexcept ;
    TokenNumber getConstantNumber(const TokenName& name) noexcept ;
    OptionalSymbolsString isParsingStateNormal(ParsingState state, Symbol startSymbol,
        Symbol endSymbol,TokenLine line, TokenColumn columnStart, TokenColumn columnEnd);

private:
	Context m_context;
    TokensInfoVector m_tokensInfoVector;
    StringVector m_errors;
};

