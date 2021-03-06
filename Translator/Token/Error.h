#pragma once

#include "BaseElement.h"
class Error : public BaseElement
{
public:
    Error (const Context& context);
    Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) override ;
    OptionalSymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;
    ~Error() override = default;
};

