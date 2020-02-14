

#include <iostream>
#include "FunctionList.h"

FunctionList::FunctionList(const Context& context)
    : BaseTreeElement{context}
    , m_function{context}
{}


void FunctionList::Print()
{
    std::cout << "<function-list>\n";
    m_function.Print();
    std::cout << "<function-list>\n";
}