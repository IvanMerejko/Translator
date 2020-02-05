#pragma once

#include "BaseElement.h"
#include "../Context.h"
class WhiteSpace : public BaseElement
{
public:
    WhiteSpace(const Context& context);
    OptionalSymbol ParseElement(std::iostream& file) override;
    SymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
};

