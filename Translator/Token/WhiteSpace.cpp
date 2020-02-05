#include "WhiteSpace.h"
#include "BaseElement.h"
#include "../Context.h"
#include "../Common/TypesFmd.h"
#include "../Common/Utils.h"

WhiteSpace::WhiteSpace(const Context& context)
    :BaseElement{context}
{}

Symbol WhiteSpace::ParseElement(std::iostream& file)
{
    Symbol currentSymbol{};
    while ( file.get(currentSymbol))
    {
        const auto symbolCategory = GetSymbolCategories(currentSymbol, m_context);
        if( symbolCategory != Categories::WhiteSpace)
        {
            return currentSymbol;
        }
    }
    return EOF;
}
SymbolsString WhiteSpace::GetParsedElementInString() const noexcept
{
    return {};
}