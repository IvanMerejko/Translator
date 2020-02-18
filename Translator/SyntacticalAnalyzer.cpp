//
// Created by Ivan on 12.02.2020.
//

#include "SyntacticalAnalyzer.h"
#include "Common/ParsingException.h"



Table CreateTable()
{
    using Error = ErrorInKnutTable;
    Table table
    {
        line(SignalProgram           ,Program                                                 ,true           ,std::nullopt ),//0
        line(Program                 ,&SyntacticalAnalyzer::checkProgram                      ,std::nullopt   ,Error::ExpectedProgram),//1
        line(std::nullopt            ,&SyntacticalAnalyzer::checkProcedureIdentifier          ,std::nullopt   ,Error::ExpectedIdentifier),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkSemicolon                    ,std::nullopt   ,Error::ExpectedSemicolon),
        line(std::nullopt            ,Block                                                   ,std::nullopt   ,std::nullopt),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkEOF                          ,true           ,Error::ExpectedEOF),
        line(Block                   ,Declarations                                            ,true           ,std::nullopt),//6
        line(std::nullopt            ,&SyntacticalAnalyzer::checkBegin                        ,std::nullopt   ,Error::ExpectedBegin),
        line(std::nullopt            ,StatementList                                           ,std::nullopt   ,Error::ExpectedSemicolon),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkEnd                          ,std::nullopt   ,Error::ExpectedEnd),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkDot                          ,std::nullopt   ,Error::ExpectedDot),
        line(Declarations            ,MathFunctionDeclaration                                 ,true           ,std::nullopt),//11
        line(MathFunctionDeclaration ,&SyntacticalAnalyzer::checkEmptyMathFunctionDeclaration ,true           ,std::nullopt),//12
        line(std::nullopt            ,&SyntacticalAnalyzer::checkDeffunc                      ,std::nullopt   ,Error::ExpectedDeffunc),
        line(std::nullopt            ,FunctionList                                            ,std::nullopt   ,Error::ExpectedSemicolon),
        line(FunctionList            ,&SyntacticalAnalyzer::checkEmptyFunctionList            ,true           ,std::nullopt),//15
        line(std::nullopt            ,Function                                                ,std::nullopt   ,std::nullopt),
        line(std::nullopt            ,FunctionList                                            ,true           ,std::nullopt),
        line(Function                ,&SyntacticalAnalyzer::checkFunctionIdentifier           ,std::nullopt   ,Error::ExpectedIdentifier),//18
        line(std::nullopt            ,&SyntacticalAnalyzer::checkEqualSymbol                  ,std::nullopt   ,Error::ExpectedEqualSymbol),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkConstant                     ,std::nullopt   ,Error::ExpectedConstant),
        line(std::nullopt            ,FunctionCharacteristic                                  ,true           ,std::nullopt),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkSemicolon                    ,true           ,Error::ExpectedSemicolon),
        line(FunctionCharacteristic  ,&SyntacticalAnalyzer::checkDivisionSymbol               ,std::nullopt   ,Error::ExpectedDivisionSymbol),//23
        line(std::nullopt            ,&SyntacticalAnalyzer::checkUnsignedInteger              ,std::nullopt   ,Error::ExpectedUnsignedInteger),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkComma                        ,std::nullopt   ,Error::ExpectedComma),
        line(std::nullopt            ,&SyntacticalAnalyzer::checkUnsignedInteger              ,true           ,Error::ExpectedUnsignedInteger),
        line(StatementList           ,&SyntacticalAnalyzer::checkEmptyStatementList           ,true           ,Error::ExpectedEmptyStatementList),//27

    };
}


ErrorContext::ErrorContext(ErrorInKnutTable type)
    : m_error{type}
    , m_info{}
{}

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
bool SyntacticalAnalyzer::checkProgram(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkProcedureIdentifier(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkFunctionIdentifier(const TokensInfoVector& tokens, int& currentToken) const
{

}

bool SyntacticalAnalyzer::checkSemicolon(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkBegin(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkEnd(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkDot(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkDeffunc(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkEmptyMathFunctionDeclaration(const TokensInfoVector& tokens, int& currentToken) const
{

}

bool SyntacticalAnalyzer::checkEmptyFunctionList(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkEqualSymbol(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkConstant(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkDivisionSymbol(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkComma(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkEmptyStatementList(const TokensInfoVector& tokens, int& currentToken) const
{

}
bool SyntacticalAnalyzer::checkEOF(const TokensInfoVector& tokens, int& currentToken) const
{

}

