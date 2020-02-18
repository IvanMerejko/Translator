//
// Created by Ivan on 13.02.2020.
//

#include <iostream>
#include <iomanip>
#include "SignalProgram.h"


SignalProgram::SignalProgram(const Context& context)
    : BaseTreeElement{context}
    , m_program{context}
{}
bool SignalProgram::operator()(const TokensInfoVector& tokens, int& currentToken)
{
    m_program(tokens, currentToken);
}
void SignalProgram::Print(int step)
{
    std::cout  << "<signal-program>\n";
    m_program.Print(step + 3);
}