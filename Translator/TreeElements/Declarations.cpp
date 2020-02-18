//
// Created by Ivan on 12.02.2020.
//

#include <iostream>
#include "Declarations.h"

Declarations::Declarations(const Context& context)
    : BaseTreeElement{context}
    , m_mathFunctionDeclaration{context}
{}
bool Declarations::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    m_mathFunctionDeclaration(tokens, currentToken);
    return true;
}

void Declarations::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<declaration>\n";
    m_mathFunctionDeclaration.Print(count + 3);
}