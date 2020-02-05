#pragma once

#include "BaseElement.h"
#include "../Common/TypesFmd.h"
#include <iostream>
class Digit : public BaseElement
{
public:
    Digit(Symbol startDigit, const Context& context);
    OptionalSymbol ParseElement(std::iostream& file) override;
    SymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~Digit() override = default;

private:
    SymbolsString m_digit;
};

