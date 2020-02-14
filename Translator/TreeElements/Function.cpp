

#include <iostream>
#include "Function.h"


Function::Function(const Context& context)
    : BaseTreeElement{context}
    , m_functionCharacteristic{context}
    , m_params{}
{}
bool Function::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    if (!checkIdentifier(tokens, currentToken))
    {
        return false;
    }
    m_params.m_identifier = tokens[currentToken++];
    if (!checkSymbol(tokens, currentToken))
    {
        return false;
    }
    m_params.m_symbol = tokens[currentToken++];
    if (!checkConstant(tokens, currentToken))
    {
        return false;
    }
    m_params.m_constant = tokens[currentToken++];
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

void Function::Print()
{
    std::cout << "<function>\n";
    {
        std::cout << "<procedure-ident>\n";
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_identifier;
        std::cout << tokenNumber << " " << tokenName << '\n';
        std::cout << "<procedure-ident>\n";
    }
    {
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_symbol;
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    {
        std::cout << "<unsigned-integer>\n";
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_constant;
        std::cout << tokenNumber << " " << tokenName << '\n';
        std::cout << "<unsigned-integer>\n";
    }
//    m_functionList.Print();
    std::cout << "<function>\n";
}
