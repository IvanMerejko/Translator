#pragma once

#include "../Context.h"
#include <iostream>
class BaseElement
{
public:
    explicit BaseElement(const Context& context)
        : m_context{context}
        , m_parsingState{}{};

    virtual Symbol ParseElement(std::iostream& file) = 0;
    virtual SymbolsString GetParsedElementInString() const noexcept = 0;
    virtual ParsingState GetElementParsingState() const noexcept = 0;
    virtual ~BaseElement() = default;

protected:
    Context m_context;
    ParsingState m_parsingState;
};
