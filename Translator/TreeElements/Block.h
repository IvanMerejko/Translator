#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"
#include "StatementList.h"
#include "../Common/Constants.h"

struct Block : public BaseTreeElement
{
    struct Params
    {
        TokenInfo m_begin;
        TokenInfo m_end;
    };
    Block(const Context& context);
    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, Declarations>, void>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {
        m_declarations(tokens, currentToken);
        if(!checkBegin(tokens, currentToken))
        {
            utils::ThrowException(MustBeBeginString, tokens, currentToken);
        }
        m_params.m_begin = tokens[currentToken++];
        if(!checEnd(tokens, currentToken))
        {
            utils::ThrowException(MustBeEndString, tokens, currentToken);
        }
        m_params.m_end = tokens[currentToken++];
    }

    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, StatementList>, void>
    operator()(const TokensInfoVector& tokens, int& currentToken)
    {

    }
    void Print(int count);

private:
    bool checkBegin(const TokensInfoVector& tokens, int& currentToken);
    bool checEnd(const TokensInfoVector& tokens, int& currentToken);
private:
    Params m_params;
    Declarations m_declarations;
    StatementList m_statementList;

};

