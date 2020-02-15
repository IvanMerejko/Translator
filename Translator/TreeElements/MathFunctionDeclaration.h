#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include "FunctionList.h"
#include <type_traits>

struct MathFunctionDeclaration : public BaseTreeElement
{
    struct Params
    {
        TokenInfo m_deffunc;
    };
    MathFunctionDeclaration(const Context& context);

    void operator()(const TokensInfoVector& tokens, int& currentToken);

    void Print(int count);

private:
    bool checkDeffunc(const TokensInfoVector& tokens, int& currentToken);
private:
    bool m_isEmpty;
    Params m_params;
    FunctionList m_functionList;
};


