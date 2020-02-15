
#include "FunctionCharacteristic.h"
#include "../Common/Constants.h"

FunctionCharacteristic::FunctionCharacteristic(const Context& context)
    : BaseTreeElement{context}
    , m_params{}
{}

void FunctionCharacteristic::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    if(!checkFirstSymbol(tokens, currentToken))
    {
        utils::ThrowException(" Must be \\ symbol.", tokens, currentToken);
    }
    m_params.m_firstSymbol = tokens[currentToken++];
    if(!checkFirstUnsignedInteger(tokens, currentToken))
    {
        utils::ThrowException(MustBeUnsignedIntegerString, tokens, currentToken);
    }
    m_params.m_firstUnsignedInteger = tokens[currentToken++];
    if(!checkSecondSymbol(tokens, currentToken))
    {
        utils::ThrowException(" Must be ',' symbol.", tokens, currentToken);
    }
    m_params.m_secondSymbol = tokens[currentToken++];
    if(!checkSecondUnsignedInteger(tokens, currentToken))
    {
        utils::ThrowException(MustBeUnsignedIntegerString, tokens, currentToken);
    }
    m_params.m_secondUnsignedInteger = tokens[currentToken++];
}

bool FunctionCharacteristic::checkFirstSymbol(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == "\\";
}
bool FunctionCharacteristic::checkFirstUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& identifiers = m_context.GetConstants();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return identifiers.find(tokenName) != identifiers.end();
}
bool FunctionCharacteristic::checkSecondSymbol(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == ",";
}
bool FunctionCharacteristic::checkSecondUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& identifiers = m_context.GetConstants();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return identifiers.find(tokenName) != identifiers.end();
}
void FunctionCharacteristic::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<function-сharacteristic>\n";
    {
        utils::PrintSeparator(count+3);
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_firstSymbol;
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    {
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_firstUnsignedInteger;
        utils::PrintUnsignedInteger(count+3, tokenNumber, tokenName);
    }
    {
        utils::PrintSeparator(count+3);
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_secondSymbol;
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    {
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_secondUnsignedInteger;
        utils::PrintUnsignedInteger(count+3, tokenNumber, tokenName);
    }
    utils::PrintSeparator(count);
    std::cout << "<function-сharacteristic>\n";
}