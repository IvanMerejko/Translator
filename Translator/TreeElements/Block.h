#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"

struct Block : public BaseTreeElement
{
    Block(const Context& context);

private:
    Declarations m_declarations;


};

