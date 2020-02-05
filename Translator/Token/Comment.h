#pragma once

#include "BaseElement.h"
class Comment : public BaseElement
{
public:
    Comment(const Context& context);
    OptionalSymbol ParseElement(std::iostream& file) override;
    SymbolsString GetParsedElementInString() const noexcept override;
    ParsingState GetElementParsingState() const noexcept override ;

private:
    bool isBeginningEndComment(Symbol symbol) const noexcept ;
    bool isEndOfComment(Symbol symbol) const noexcept ;
};



