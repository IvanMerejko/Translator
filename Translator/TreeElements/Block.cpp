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
    {
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_begin;
        utils::PrintSeparator(count+3);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    {
        const auto& [tokenName, tokenNumber, line, column] = m_params.m_end;
        utils::PrintSeparator(count+3);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    utils::PrintSeparator(count);
    std::cout << "<block>\n";
}

bool Block::checkBegin(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find("BEGIN")->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}
bool Block::checEnd(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find("END")->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}