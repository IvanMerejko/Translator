#pragma once

#include "../Context.h"
struct BaseTreeElement
{
    explicit BaseTreeElement(const Context& context)
        :m_context{context}
    {}
    ~BaseTreeElement() = default;

protected:
    Context m_context;
};

struct Empty{};