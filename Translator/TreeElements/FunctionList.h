#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include <type_traits>

struct FunctionList : public BaseTreeElement
{
    explicit FunctionList(const Context& context);

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Function>, bool>
            operator()(const TokensInfoVector& tokens, int& currentToken)
    {
        m_function(tokens, currentToken);
    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Empty>, bool>
        operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }

    void Print();

private:
    Function m_function;
};



