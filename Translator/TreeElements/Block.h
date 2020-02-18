#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"
#include "StatementList.h"
#include "../Common/Constants.h"

struct Block : public BaseTreeElement
{
    struct Params
    {
        Params() = default;
        OptionalTokenInfo m_begin;
        OptionalTokenInfo m_end;
        OptionalTokenInfo m_dot;
    };
    Block(const Context& context);

    void operator()(const TokensInfoVector& tokens, int& currentToken);

    void Print(int count);

private:
    bool checkBegin(const TokensInfoVector& tokens, int& currentToken);
    bool checkEnd(const TokensInfoVector& tokens, int& currentToken);
    bool checkDot(const TokensInfoVector& tokens, int& currentToken);
private:
    Params m_params;
    Declarations m_declarations;
    StatementList m_statementList;

};

