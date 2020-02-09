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
        const auto symbolCategory = utils::GetSymbolCategories(currentSymbol, m_context);
        if( symbolCategory == Categories::StartIdentifier ||
            symbolCategory == Categories::StartConstant)
        {
            m_identifier.append(1, currentSymbol);
            continue;
        }
        if(!utils::IsSpace(currentSymbol))
        {
            m_parsingState = ParsingState::ErrorIncorrectSymbolAfterIdentifier;
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
    return m_parsingState;
}