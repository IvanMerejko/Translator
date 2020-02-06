#pragma once

#include "BaseElement.h"
class Identifier : public BaseElement
{
public:
    Identifier (Symbol startLetter, const Context& context);
    Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) override ;
    OptionalSymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~Identifier() override = default;
private:
    SymbolsString m_identifier;
};

