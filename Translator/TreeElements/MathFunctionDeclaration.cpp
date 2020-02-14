
#include <iostream>
#include "MathFunctionDeclaration.h"
#include "../Common/Constants.h"

MathFunctionDeclaration::MathFunctionDeclaration(const Context& context)
    : BaseTreeElement{context}
    , m_functionList{context}
{}


void MathFunctionDeclaration::Print()
{
    std::cout << "<math-function-declaration>\n";
    m_functionList.Print();
    std::cout << "<math-function-declaration>\n";
}

bool MathFunctionDeclaration::checkDeffunc(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& deffuncNumber = keywords.find(DeffuncString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return deffuncNumber == tokenNumber;
}