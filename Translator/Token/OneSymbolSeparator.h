#pragma one

#include "BaseElement.h"
class OneSymbolSeparator : public BaseElement
{
public:
    OneSymbolSeparator(Symbol separator, const Context& context);
    Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) override ;
    OptionalSymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~OneSymbolSeparator() override = default;
private:
    SymbolsString m_separator;
};



