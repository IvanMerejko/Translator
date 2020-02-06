#pragma once

#include "BaseElement.h"
class Comment : public BaseElement
{
public:
    Comment(const Context& context);
    Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) override;
    OptionalSymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;

private:
    bool isBeginningEndComment(Symbol symbol) const noexcept ;
    bool isEndOfComment(Symbol symbol) const noexcept ;
};



