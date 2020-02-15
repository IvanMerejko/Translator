//
// Created by Ivan on 12.02.2020.
//

#include "SyntacticalAnalyzer.h"
#include "Common/ParsingException.h"


SyntacticalAnalyzer::SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector)
    : m_context{context}
    , m_tokensInfoVector{tokensInfoVector}
    , m_signalProgram{context}
{}
void SyntacticalAnalyzer::StartAnalyze()
{
    int start{0};
    try
    {
        m_signalProgram(m_tokensInfoVector, start);
        m_signalProgram.Print(0);
    }
    catch (const ParsingException& error)
    {
        m_signalProgram.Print(0);
        std::cout << "\n\n" << error.what();
    }


}