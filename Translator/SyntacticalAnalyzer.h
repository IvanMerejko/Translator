//
// Created by Ivan on 12.02.2020.
//

#ifndef TRANSLATOR_SYNTACTICALANALYZER_H
#define TRANSLATOR_SYNTACTICALANALYZER_H


#include "Common/TypesFmd.h"
#include "Context.h"
#include "TreeElements/SignalProgram.h"

class SyntacticalAnalyzer
{
public:
    SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector);
    void StartAnalyze() ;
private:
    Context m_context;
    TokensInfoVector m_tokensInfoVector;
    SignalProgram m_signalProgram;
};


#endif //TRANSLATOR_SYNTACTICALANALYZER_H
