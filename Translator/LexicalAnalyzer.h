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
private:
    UpElement getElementPointer(Symbol currentSymbol, Categories category, TokenLine line, TokenColumn column);
    /// return next symbol if it not equal to <, as comment start like *<
    OptionalSymbol specialCaseForCommentStart(std::ifstream& file) const;
    TokenNumber getTokenNumber(const TokenName& name, Categories category) noexcept ;
    TokenNumber getIdentifierNumber(const TokenName& name) noexcept ;
    TokenNumber getOneSymbolSeparatorNumber(Symbol symbol) const noexcept ;
    TokenNumber getConstantNumber(const TokenName& name) noexcept ;
    std::string createErrorStringOfIncorrectSymbol(Symbol name, TokenLine line, TokenColumn column) const ;
private:
	Context m_context;
    TokensInfoVector m_tokensInfoVector;
    StringVector m_errors;
};

