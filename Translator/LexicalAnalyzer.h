#pragma once
#include <string_view>
#include <filesystem>
#include <map>
#include <set>
namespace fs = std::filesystem;
using InitialSymbolsCategories = std::map<int, std::set<int>>;
class LexicalAnalyzer
{
public:
	enum class SymbolType
	{
		Digit = 0,
		Identifier = 1,
		WhiteSpace = 2,
		Error = 100,
	};
public:
	explicit LexicalAnalyzer(std::string_view file_name);
	void StartAnalyze();
private:
	InitialSymbolsCategories m_initialSymbolsCategories;
};

