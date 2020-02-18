

#include <iostream>
#include "FunctionList.h"
#include "../Common/Constants.h"

FunctionList::FunctionList(const Context& context)
    : BaseTreeElement{context}
    , m_function{context}
    , m_isEmpty{false}
{}


void FunctionList::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<function-list>\n";
    if(m_isEmpty)
    {
        utils::PrintEmpty(count+3);
        return;
    }
    else
    {
        m_function.Print(count+3);
    }
    if(m_nextFunctionList)
    {
        m_nextFunctionList->Print(count+3);
    }
    else
    {
        utils::PrintSeparator(count+3);
        std::cout << "<function-list>\n";
        utils::PrintEmpty(count+3);
    }
}
bool FunctionList::checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& identifiers = m_context.GetIdentifiers();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return identifiers.find(tokenName) != identifiers.end();
}

void FunctionList::operator()(const TokensInfoVector &tokens, int &currentToken)
{
    if(!checkIdentifier(tokens, currentToken))
    {
        m_isEmpty = true;
        return;
    }
    m_function(tokens, currentToken);
    if(checkIdentifier(tokens, currentToken))
    {
        m_nextFunctionList = std::make_shared<FunctionList>(m_context);
        (*m_nextFunctionList)(tokens, currentToken);
    }
}