#pragma once

#include "BaseTreeElement.h"
#include "Declarations.h"
#include "Block.h"
#include "Program.h"


struct SignalProgram : public BaseTreeElement
{
    SignalProgram(const Context& context);
    bool operator()(const TokensInfoVector& tokens, int& currentToken);
    void Print(int step);
private:
    Program m_program;
};

