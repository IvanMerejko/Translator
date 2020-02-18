//
// Created by Ivan on 12.02.2020.
//

#include <iostream>
#include "Block.h"

Block::Block(const Context& context)
    : BaseTreeElement{context}
    , m_declarations{context}
    , m_statementList{context}
{}

void Block::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<block>\n";
    m_declarations.Print(count+3);
    if (m_params.m_begin){
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_begin;
        utils::PrintSeparator(count+3);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    else
    {
        return;
    }
    m_statementList.Print(count+3);
    if(m_params.m_end)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_end;
        utils::PrintSeparator(count+3);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    else
    {
        return;
    }
    if(m_params.m_dot)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_dot;
        utils::PrintSeparator(count+3);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    else
    {
        return;
    }
}

bool Block::checkBegin(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find(BeginString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}
bool Block::checkEnd(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find(EndString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}
bool Block::checkDot(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == ".";
}

void Block::operator()(const TokensInfoVector &tokens, int &currentToken)
{
    m_declarations(tokens, currentToken);
    if(!checkBegin(tokens, currentToken))
    {
        utils::ThrowException(MustBeBeginString, tokens, currentToken);
    }
    m_params.m_begin = tokens[currentToken++];
    m_statementList(tokens, currentToken);
    if(!checkEnd(tokens, currentToken))
    {
        utils::ThrowException(MustBeEndString, tokens, currentToken);
    }
    m_params.m_end = tokens[currentToken++];
    if(!checkDot(tokens, currentToken))
    {
        utils::ThrowException("Must be '.' .", tokens, currentToken);
    }
    m_params.m_dot = tokens[currentToken++];
}