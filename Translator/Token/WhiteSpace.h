#pragma once

#include "BaseElement.h"
#include "../Context.h"
class WhiteSpace : public BaseElement
{
public:
    WhiteSpace(const Context& context);
    Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) override;
    OptionalSymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~WhiteSpace() override = default;
};

