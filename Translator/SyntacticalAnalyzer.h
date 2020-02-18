//
// Created by Ivan on 12.02.2020.
//

#ifndef TRANSLATOR_SYNTACTICALANALYZER_H
#define TRANSLATOR_SYNTACTICALANALYZER_H


#include "Common/TypesFmd.h"
#include "Context.h"
#include "TreeElements/SignalProgram.h"
#include <variant>
#include <tuple>
#include <optional>

enum Address
{
    SignalProgram = 0,
    Program = 1,
    Block = 6,
    Declarations = 11,
    MathFunctionDeclaration = 12,
    FunctionList = 15,
    Function = 18,
    FunctionCharacteristic = 23,
    StatementList = 27
};

struct ErrorContext
{
    ErrorContext(ErrorInKnutTable type);
    ErrorInKnutTable m_error;
    TokenInfo m_info;
};
class SyntacticalAnalyzer;
using functionChecker = bool (SyntacticalAnalyzer::*)(const TokensInfoVector&, int&) const;

using oneLine = std::tuple< std::optional<Address>,
                            std::variant<int, functionChecker>,
                            std::optional<bool>,
                            std::optional<ErrorContext>>;
constexpr auto line = std::make_tuple<  std::optional<Address>,
                                        std::variant<int, functionChecker>,
                                        std::optional<bool>,
                                        std::optional<ErrorContext>>;
using Table = std::array<oneLine, 28>;


class SyntacticalAnalyzer
{
public:
    friend Table CreateTable();
    SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector);
    void StartAnalyze() ;

private:
    bool checkProgram(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkProcedureIdentifier(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkFunctionIdentifier(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkSemicolon(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkDot(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkBegin(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEnd(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkDeffunc(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEmptyMathFunctionDeclaration(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEmptyFunctionList(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEmptyStatementList(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEqualSymbol(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkConstant(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkUnsignedInteger(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkDivisionSymbol(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkComma(const TokensInfoVector& tokens, int& currentToken) const;
    bool checkEOF(const TokensInfoVector& tokens, int& currentToken) const;
private:
    Context m_context;
    TokensInfoVector m_tokensInfoVector;
    SignalProgram m_signalProgram;
    Table m_table;
};


#endif //TRANSLATOR_SYNTACTICALANALYZER_H
