#pragma once

#include "BaseTreeElement.h"
#include "FunctionCharacteristic.h"
#include "Function.h"
#include <type_traits>

struct FunctionList : public BaseTreeElement
{
    using FunctionListPtr = std::shared_ptr<FunctionList>;
    explicit FunctionList(const Context& context);

    bool operator()(const TokensInfoVector& tokens, int& currentToken);



    void Print(int count);

private:
    bool checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const;
private:
    bool m_isEmpty;
    FunctionListPtr m_nextFunctionList;
    Function m_function;
};



