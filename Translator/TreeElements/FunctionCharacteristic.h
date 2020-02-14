#pragma once
#include "../Common/Utils.h"
#include "BaseTreeElement.h"
struct FunctionCharacteristic : public BaseTreeElement
{
    FunctionCharacteristic(const Context& context);
    bool operator()(const TokensInfoVector& tokens, int& currentToken);
};



