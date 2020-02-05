#pragma once

#include "BaseElement.h"
class Identifier : public BaseElement
{
public:
    Identifier (Symbol startLetter, const Context& context);
    OptionalSymbol ParseElement(std::iostream& file) override ;
    SymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~Identifier() override = default;
private:
    SymbolsString m_identifier;
};

