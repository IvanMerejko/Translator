//
// Created by Ivan on 13.02.2020.
//

#include <iostream>
#include <iomanip>
#include "Program.h"
#include "../Common/Constants.h"
#include "../Common/ParsingException.h"


Program::Program(const Context& context)
    : BaseTreeElement{context}
    , m_block{context}
    , m_params{}
{}

void Program::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    if(!checkStart(tokens, currentToken))
    {
        utils::ThrowException(MustBeProgramString, tokens, currentToken);
    }
    m_params.m_start = tokens[currentToken++];
    if(!checkIdentifier(tokens, currentToken))
    {
        utils::ThrowException(MustBeIdentifierString, tokens, currentToken);
    }
    m_params.m_procedureIdentifier = tokens[currentToken++];
    if(!checkSeparator(tokens, currentToken))
    {
        utils::ThrowException(MustBeSemicolonString, tokens, currentToken);
    }
    m_params.m_symbol = tokens[currentToken++];
    m_block(tokens, currentToken);
}

bool Program::checkStart(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find(ProgramString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}
bool Program::checkIdentifier(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& identifiers = m_context.GetIdentifiers();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return identifiers.find(tokenName) != identifiers.end();
}
bool Program::checkSeparator(const TokensInfoVector& tokens, int& currentToken) const
{
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == ";";
}

void Program::Print(int step)
{
    utils::PrintSeparator(step);
    step += 3;
    std::cout << "<program>\n";
    if(m_params.m_start)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_start;
        utils::PrintSeparator(step);
        std::cout << tokenNumber << " " << tokenName << '\n';
    }
    else
    {
        return;
    }
    if(m_params.m_procedureIdentifier)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_procedureIdentifier;
        utils::PrintProcedureIdentifier(step, tokenNumber, tokenName);
    }
    else
    {
        return;
    }
    if(m_params.m_symbol)
    {
        const auto& [tokenName, tokenNumber, line, column] = *m_params.m_symbol;
        utils::PrintSeparator(step);
        std::cout << tokenNumber << " " << tokenName << '\n';
        step -= 3;
    }
    else
    {
        return;
    }
    m_block.Print(step+3);
}