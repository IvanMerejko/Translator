#include "LexicalAnalyzer.h"
#include <type_traits>
#include "Common/TypesFmd.h"
#include "Common/Utils.h"


namespace
{
	template <typename T, typename = std::enable_if_t<std::is_same_v<T, Categories>>>
	int EnumToInt(T value)
	{
		return static_cast<int>(value);
	}

	auto IntToEnum(int value)
	{
		return static_cast<Categories>(value);
	}

}


//LexicalAnalyzer::LexicalAnalyzer(std::string_view file_name)
//	: m_initialSymbolsCategories(GetSymbolsCategories())
//{
//}

Categories LexicalAnalyzer::getSymbolCategories(Symbol symbol)
{
    const auto& symbolsCategories = m_context.GetSymbolsCategories();
    const auto it = symbolsCategories.find(CharToInt(symbol));
    if(it != symbolsCategories.end())
    {
        return it->second;
    }
    return Categories::ErrorSymbol;
}

void LexicalAnalyzer::StartAnalyze()
{

}
