//
// Created by Ivan on 12.02.2020.
//

#ifndef TRANSLATOR_SYNTACTICALANALYZER_H
#define TRANSLATOR_SYNTACTICALANALYZER_H


#include "Common/TypesFmd.h"
#include "Context.h"
#include "TreeElements/SignalProgram.h"
#include "TreeElements/Tree.h"
#include <variant>
#include <tuple>
#include <optional>

struct ErrorContext
{
    ErrorContext(ErrorInKnutTable type);
    ErrorInKnutTable m_error;
    TokenInfo m_info;
};

enum class State
{
	Normal,
	Error,
	NoCall
};
class SyntacticalAnalyzer;
using functionChecker = bool (SyntacticalAnalyzer::*)(const TokensInfoVector&, int&, NodePtr& ) const;

using oneLine = std::tuple< std::optional<Address>,
                            std::variant<int, functionChecker>,
                            std::optional<bool>,
                            std::optional<ErrorContext>>;
constexpr auto line = std::make_tuple<  std::optional<Address>,
                                        std::variant<int, functionChecker>,
                                        std::optional<bool>,
                                        std::optional<ErrorContext>>;
using Table = std::array<oneLine, 28>;
using TablePtr = std::shared_ptr<Table>;

class SyntacticalAnalyzer
{
public:
    friend TablePtr CreateTable();
    SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector);
    void StartAnalyze() ;

private:
    bool checkProgram(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkProcedureIdentifier(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkFunctionIdentifier(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkSemicolon(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkDot(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkBegin(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEnd(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkDeffunc(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEmptyMathFunctionDeclaration(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEmptyFunctionList(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEmptyStatementList(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEqualSymbol(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkConstant(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkUnsignedInteger(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkDivisionSymbol(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkComma(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool checkEOF(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const;
    bool isTerminal(const oneLine& lineInfo) const;
    std::optional<ErrorContext> parse(int currentLine, int& currentToken, NodePtr& node);
	bool if_AT(int& currentLine, int& currentToken, NodePtr& node);
private:
    Context m_context;
    TokensInfoVector m_tokensInfoVector;
    //SignalProgram m_signalProgram;
    Tree m_tree;
	TablePtr m_table;
};


#endif //TRANSLATOR_SYNTACTICALANALYZER_H
