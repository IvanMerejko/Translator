#include "Identifier.h"
#include "../Common/TypesFmd.h"
#include "../Common/Utils.h"
#include <fstream>
Identifier::Identifier (Symbol startLetter, const Context& context)
 : BaseElement{context}
 , m_identifier{startLetter}
{

}
Symbol Identifier::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol currentSymbol{};
    while ( file.get(currentSymbol))
    {
        ++column;
        const auto symbolCategory = GetSymbolCategories(currentSymbol, m_context);
        if( symbolCategory == Categories::StartIdentifier ||
            symbolCategory == Categories::StartConstant)
        {
            m_identifier.append(1, currentSymbol);
            continue;
        }
        return currentSymbol;
    }
    return EOF;
}

OptionalSymbolsString Identifier::GetParsedElementInString() const noexcept
{
    return m_identifier;
}

ParsingState Identifier::GetElementParsingState() const noexcept
{
    return ParsingState::Normal;
}