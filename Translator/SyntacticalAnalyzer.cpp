//
// Created by Ivan on 12.02.2020.
//

#include "SyntacticalAnalyzer.h"


SyntacticalAnalyzer::SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector)
    : m_context{context}
    , m_tokensInfoVector{tokensInfoVector}
    , m_signalProgram{context}
{}
void SyntacticalAnalyzer::StartAnalyze()
{
    int start{0};
    m_signalProgram(m_tokensInfoVector, start);
    m_signalProgram.Print(0);
}