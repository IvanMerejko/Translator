
#include <iostream>
#include "MathFunctionDeclaration.h"
#include "../Common/Constants.h"

MathFunctionDeclaration::MathFunctionDeclaration(const Context& context)
    : BaseTreeElement{context}
    , m_functionList{context}
    , m_isEmpty{false}
{}


void MathFunctionDeclaration::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<math-function-declaration>\n";
    if(m_isEmpty)
    {
        utils::PrintEmpty(count+3);
        count += 3;
    }
    else
    {
        if(m_params.m_deffunc)
        {
            const auto& [tokenName, tokenNumber, line, column] = *m_params.m_deffunc;
            utils::PrintSeparator(count+3);
            std::cout << tokenNumber << " " << tokenName << '\n';
            count += 3;
        }
        else
        {
            return;
        }
        m_functionList.Print(count+3);
    }
}

bool MathFunctionDeclaration::checkDeffunc(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& deffuncNumber = keywords.find(DeffuncString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return deffuncNumber == tokenNumber;
}

void MathFunctionDeclaration::operator()(const TokensInfoVector &tokens, int &currentToken)
{
    if(!checkDeffunc(tokens, currentToken))
    {
        m_isEmpty = true;
        return;
    }
    m_params.m_deffunc = tokens[currentToken++];
    m_functionList(tokens, currentToken);
}