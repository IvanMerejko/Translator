#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include <type_traits>

struct FunctionList : public BaseTreeElement
{
    explicit FunctionList(const Context& context);

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Function>, OptionalSymbolsString>
            operator()(const TokensInfoVector& tokens, int& currentToken)
    {
        this->operator()<Function>(tokens, currentToken);
    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Empty>, OptionalSymbolsString>
        operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }



private:
    Function m_function;
};



