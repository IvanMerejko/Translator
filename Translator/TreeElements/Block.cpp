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

void Block::Print()
{
    std::cout << "<block>\n";
    m_declarations.Print();
    std::cout << "<block>\n";
}