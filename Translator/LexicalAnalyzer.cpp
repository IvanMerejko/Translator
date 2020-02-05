#include "LexicalAnalyzer.h"
#include <type_traits>
#include <fstream>
#include "Common/TypesFmd.h"
#include "Common/Utils.h"
#include "Token/WhiteSpace.h"
#include "Token/Digit.h"
#include "Token/Identifier.h"
#include "Token/Comment.h"
#include <memory>

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



void LexicalAnalyzer::StartAnalyze(std::string_view file_name)
{
    std::ifstream file(file_name.data());
    Symbol currentSymbol{};
    while(file.get(currentSymbol))
    {
        const auto symbolCategory = GetSymbolCategories(currentSymbol, m_context);
        const auto tokenPointer = getElementPointer(currentSymbol, symbolCategory);

    }
}

UpElement LexicalAnalyzer::getElementPointer(Symbol currentSymbol,Categories category) const
{
    switch (category)
    {
        case Categories::WhiteSpace:
            return std::make_unique<WhiteSpace>(m_context);
        case Categories::StartConstant:
            return std::make_unique<Digit>(currentSymbol, m_context);
        case Categories::StartIdentifier:
            return std::make_unique<Identifier>(currentSymbol, m_context);
        case Categories::StartComment:
            return std::make_unique<Comment>(m_context);
        case Categories::ErrorSymbol:
        {
        }break;
    }
}