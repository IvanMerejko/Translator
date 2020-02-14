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

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, FunctionList>, bool>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {
        if(!checkDeffunc(tokens, currentToken))
        {
            return false;
        }
        m_params.m_deffunc = tokens[currentToken++];
        if(m_functionList.operator()<Function>(tokens, currentToken))
        {
            m_functionList.operator()<Empty>(tokens, currentToken);
        }
    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Empty>, bool>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }
    void Print();

private:
    bool checkDeffunc(const TokensInfoVector& tokens, int& currentToken);
private:
    Params m_params;
    FunctionList m_functionList;
};


