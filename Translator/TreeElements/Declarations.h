#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include "FunctionList.h"
#include "MathFunctionDeclaration.h"
#include <type_traits>

struct Declarations : public BaseTreeElement
{
    Declarations(const Context& context);
    bool operator()(const TokensInfoVector& tokens, int& currentToken);
    void Print();
private:
    MathFunctionDeclaration m_mathFunctionDeclaration;
};
