#pragma once

#include "../Context.h"
#include <iostream>
#include "../Common/TypesFmd.h"
class BaseElement
{
public:
    BaseElement() = default;
    explicit BaseElement(const Context& context)
        : m_context{context}
        , m_parsingState{}{};

    virtual Symbol ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column) = 0;
    virtual OptionalSymbolsString GetParsedElementInString() const noexcept = 0;
    virtual ParsingState GetElementParsingState() const noexcept = 0;
    virtual ~BaseElement() = default;

protected:
    Context m_context;
    ParsingState m_parsingState;
};
using UpElement = std::unique_ptr<BaseElement>;