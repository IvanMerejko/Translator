#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"
#include "StatementList.h"

struct Block : public BaseTreeElement
{
    struct Params
    {
        TokenInfo m_begin;
        TokenInfo m_end;
    };
    Block(const Context& context);
    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Declarations>, bool>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {
        return m_declarations(tokens, currentToken);
    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, StatementList>, bool>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }
    void Print();
private:
    Params m_params;
    Declarations m_declarations;
    StatementList m_statementList;

};

