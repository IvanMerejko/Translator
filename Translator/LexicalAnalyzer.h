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

private:
    UpElement getElementPointer(Symbol currentSymbol, Categories category) const;
    /// return next symbol if it not equal to <, as comment start like *<
    OptionalSymbol specialCaseForCommentStart(std::ifstream& file) const;

private:
	Context m_context;
    TokensInfoVector m_tokensInfoVector;
};

