#pragma once
#include "../Common/Utils.h"
#include "BaseTreeElement.h"
struct FunctionCharacteristic : public BaseTreeElement
{
    struct Params
    {
        TokenInfo m_firstSymbol;
        TokenInfo m_firstUnsignedInteger;
        TokenInfo m_secondSymbol;
        TokenInfo m_secondUnsignedInteger;
    };
    FunctionCharacteristic(const Context& context);
    void operator()(const TokensInfoVector& tokens, int& currentToken);
    void Print(int count);
private:
    bool checkFirstSymbol(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkFirstUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkSecondSymbol(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkSecondUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const;
private:
    Params m_params;
};



