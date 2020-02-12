#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"

struct Function : public BaseTreeElement
{
    Function(const Context& context);
    OptionalSymbolsString operator()(const TokensInfoVector& tokens, int& currentToken);
private:
    FunctionCharacteristic m_functionCharacteristic;
};

