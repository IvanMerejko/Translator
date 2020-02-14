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
    if ( !m_mathFunctionDeclaration.operator()<FunctionList>(tokens, currentToken) )
    {
        m_mathFunctionDeclaration.operator()<Empty>(tokens, currentToken);
    }
}

void Declarations::Print()
{
    std::cout << "<declaration>\n";
    m_mathFunctionDeclaration.Print();
    std::cout << "<declaration>\n";
}