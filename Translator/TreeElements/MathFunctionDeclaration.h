#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include "FunctionList.h"
#include <type_traits>

struct MathFunctionDeclaration : public BaseTreeElement
{
    MathFunctionDeclaration(const Context& context);

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, FunctionList>, OptionalSymbolsString>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Empty>, OptionalSymbolsString>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }

private:
    FunctionList m_functionList;
};


