//
// Created by Ivan on 12.02.2020.
//

#include "Declarations.h"

Declarations::Declarations(const Context& context)
    : BaseTreeElement{context}
    , m_mathFunctionDeclaration{context}
{}
OptionalSymbolsString Declarations::operator()(const TokensInfoVector& tokens, int& currentToken)
{

}