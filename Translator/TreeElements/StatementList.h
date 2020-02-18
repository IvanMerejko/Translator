#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"

struct StatementList : public BaseTreeElement
{
    StatementList(const Context& context);
    void operator() (const TokensInfoVector& tokens, int& currentToken);
    void Print(int count);

private:
    bool isEmpty(const TokensInfoVector& tokens, int& currentToken);
};

