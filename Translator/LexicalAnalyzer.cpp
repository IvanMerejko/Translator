#include "LexicalAnalyzer.h"
#include <type_traits>

namespace
{
	template <typename T, typename = std::enable_if_t<std::is_same_v<T, LexicalAnalyzer::SymbolType>>>
	int EnumToInt(T value)
	{
		return static_cast<int>(value);
	}

	auto IntToEnum(int value)
	{
		return static_cast<LexicalAnalyzer::SymbolType>(value);
	}

	InitialSymbolsCategories GetSymbolsCategories()
	{
		using ST = LexicalAnalyzer::SymbolType;
		InitialSymbolsCategories symbolsMap
		{
			{
				EnumToInt(ST::Digit),{1, 2}				
			},
			{
				EnumToInt(ST::Identifier), {1}
			}
		};
		return symbolsMap;
	}
}


LexicalAnalyzer::LexicalAnalyzer(std::string_view file_name)
	: m_initialSymbolsCategories(GetSymbolsCategories())
{
}

void LexicalAnalyzer::StartAnalyze()
{

}
