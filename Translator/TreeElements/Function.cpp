

#include "Function.h"


Function::Function(const Context& context)
    : BaseTreeElement{context}
    , m_functionCharacteristic{context}
{}
OptionalSymbolsString Function::operator()(const TokensInfoVector& tokens, int& currentToken)
{

}
