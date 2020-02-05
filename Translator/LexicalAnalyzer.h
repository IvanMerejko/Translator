#pragma once
#include <string_view>
//#include <filesystem>
//#include <string_view>
#include "Context.h"
#include "Token/BaseElement.h"

#include <set>
//namespace fs = std::filesystem;

class LexicalAnalyzer
{
public:

public:
    LexicalAnalyzer() = default;
//	explicit LexicalAnalyzer(std::string_view file_name);
	void StartAnalyze(std::string_view file_name);

private:
    UpElement getElementPointer(Symbol currentSymbol, Categories category) const;

private:
	Context m_context;
};

