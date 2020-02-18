#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"

struct Function : public BaseTreeElement
{
    struct Params
    {
        Params() = default;
        OptionalTokenInfo m_identifier;
        OptionalTokenInfo m_symbol;
        OptionalTokenInfo m_constant;
    };
    Function(const Context& context);
    void operator()(const TokensInfoVector& tokens, int& currentToken);
    void Print(int count);

private:
    bool checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkSymbol(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkConstant(const TokensInfoVector& tokens, int& currentToken) const;
private:
    Params m_params;
    FunctionCharacteristic m_functionCharacteristic;
};

