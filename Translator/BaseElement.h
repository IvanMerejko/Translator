#pragma once

#include "Context.h"
class BaseElement
{
    explicit BaseElement(const Context& context)
        : m_context{context}{};

    virtual ~BaseElement() = default;
protected:
    Context m_context;
};
