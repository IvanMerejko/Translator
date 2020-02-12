
#include "MathFunctionDeclaration.h"

MathFunctionDeclaration::MathFunctionDeclaration(const Context& context)
    : BaseTreeElement{context}
    , m_functionList{context}
{}