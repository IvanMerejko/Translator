#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"
#include "Block.h"

struct Program : public BaseTreeElement
{
    struct Params
    {
        OptionalTokenInfo m_start;
        OptionalTokenInfo m_procedureIdentifier;
        OptionalTokenInfo m_symbol;
    };
    Program(const Context& context);
    void operator()(const TokensInfoVector& tokens, int& currentToken);
    void Print(int step);
private:
    bool checkStart(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkSeparator(const TokensInfoVector& tokens, int& currentToken) const;
private:
    Params m_params;
    Block m_block;
};


