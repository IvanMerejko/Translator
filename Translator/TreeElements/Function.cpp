

#include <iostream>
#include "Function.h"
#include "../Common/ParsingException.h"
#include "../Common/Constants.h"


Function::Function(const Context& context)
    : BaseTreeElement{context}
    , m_functionCharacteristic{context}
    , m_params{}
{}
void Function::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    if (!checkIdentifier(tokens, currentToken))
    {
        utils::ThrowException(MustBeIdentifierString, tokens, currentToken);
    }
    m_params.m_identifier = tokens[currentToken++];
    if (!checkSymbol(tokens, currentToken))
    {
        utils::ThrowException(MustBeAssignmentSymbolString, tokens, currentToken);
    }
    m_params.m_symbol = tokens[currentToken++];
    if (!checkConstant(tokens, currentToken))
    {
        utils::ThrowException(MustBeConstantString, tokens, currentToken);
    }
    m_params.m_constant = tokens[currentToken++];
    m_functionCharacteristic(tokens, currentToken);
}

bool Function::checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& identifiers = m_context.GetIdentifiers();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return identifiers.find(tokenName) != identifiers.end();
}
bool Function::checkSymbol(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == "=";
}
bool Function::checkConstant(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& constant = m_context.GetConstants();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return constant.find(tokenName) != constant.end();
}

void Function::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<function>\n";
    if(m_params.m_identifier)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_identifier;
        utils::PrintFunctionIdentifier(count + 3, tokenNumber, tokenName);
        count += 3;
    }
    else
    {
        return;
    }

    if(m_params.m_symbol)
    {
        utils::PrintSeparator(count);
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_symbol;
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    else
    {
        return;
    }

    if(m_params.m_constant)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_constant;
        utils::PrintConstant(count, tokenNumber, tokenName);
    }
    else
    {
        return;
    }
    m_functionCharacteristic.Print(count);
}
