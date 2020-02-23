//
// Created by Ivan on 12.02.2020.
//

#include "SyntacticalAnalyzer.h"
#include "Common/ParsingException.h"
#include <utility>
#include <array>


ErrorMap CreateErrorMap()
{
	using Error = ErrorInKnutTable;
	ErrorMap errorMap
	{
		{Error::ExpectedProgram,"Expected \"PROGRAM\". Found: "},
		{Error::ExpectedIdentifier,"Expected <procedure-identifier>. Found: "},
		{Error::ExpectedSemicolon,"Expected ';'. Found: "},
		{Error::ExpectedBegin,"Expected \"BEGIN\". Found: "},
		{Error::ExpectedEnd,"Expected \"END\". Found: "},
		{Error::ExpectedDot,"Expected '.'. Found: "},
		{Error::ExpectedDeffunc,"Expected \"DEFFUNC\". Found: "},
		{Error::ExpectedEqualSymbol,"Expected '='. Found: "},
		{Error::ExpectedConstant,"Expected <constant>. Found: "},
		{Error::ExpectedUnsignedInteger,"Expected <unsigned-integer>. Found: "},
		{Error::ExpectedDivisionSymbol,"Expected '\'. Found: "},
		{Error::ExpectedComma,"Expected ','. Found: "},
		{Error::ExpectedEmptyStatementList,"Expected empty <statement-list>. Found: "},
	};
	return errorMap;
}


auto GetFirstElement(const oneLine& info)
{
    return std::get<0>(info);
}

auto GetSecondElement(const oneLine& info)
{
    return std::get<1>(info);
}

auto GetThirdElement(const oneLine& info)
{
    return std::get<2>(info);
}

auto GetFourthElement(const oneLine& info)
{
    return std::get<3>(info);
}

NodePtr& CreateSubNode(NodePtr& node, NodeType type)
{
	if (type == NodeType::Child)
	{
		node->m_child = std::make_shared<Node>();
return node->m_child;
	}
	else
	{
	node->m_next = std::make_shared<Node>();
	return node->m_next;
	}
}

bool CheckState(State src, State dst)
{
	return src == dst;
}


TablePtr CreateTable()
{
	using Error = ErrorInKnutTable;
	TablePtr table = std::make_shared<Table>(std::array<oneLine, 28>
	{
		line(SignalProgramE, ProgramE, true, std::nullopt),//0
			line(ProgramE, &SyntacticalAnalyzer::checkProgram, std::nullopt, Error::ExpectedProgram),//1
			line(std::nullopt, &SyntacticalAnalyzer::checkProcedureIdentifier, std::nullopt, Error::ExpectedIdentifier),
			line(std::nullopt, &SyntacticalAnalyzer::checkSemicolon, std::nullopt, Error::ExpectedSemicolon),
			line(std::nullopt, BlockE, std::nullopt, std::nullopt),
			line(std::nullopt, &SyntacticalAnalyzer::checkEOF, true, Error::ExpectedEOF),
			line(BlockE, DeclarationsE, true, std::nullopt),//6
			line(std::nullopt, &SyntacticalAnalyzer::checkBegin, std::nullopt, Error::ExpectedBegin),
			line(std::nullopt, StatementListE, std::nullopt, Error::ExpectedSemicolon),
			line(std::nullopt, &SyntacticalAnalyzer::checkEnd, std::nullopt, Error::ExpectedEnd),
			line(std::nullopt, &SyntacticalAnalyzer::checkDot, std::nullopt, Error::ExpectedDot),
			line(DeclarationsE, MathFunctionDeclarationE, true, std::nullopt),//11
			line(MathFunctionDeclarationE, &SyntacticalAnalyzer::checkEmptyMathFunctionDeclaration, true, std::nullopt),//12
			line(std::nullopt, &SyntacticalAnalyzer::checkDeffunc, std::nullopt, Error::ExpectedDeffunc),
			line(std::nullopt, FunctionListE, std::nullopt, Error::ExpectedSemicolon),
			line(FunctionListE, &SyntacticalAnalyzer::checkEmptyFunctionList, true, std::nullopt),//15
			line(std::nullopt, FunctionE, std::nullopt, std::nullopt),
			line(std::nullopt, FunctionListE, true, std::nullopt),
			line(FunctionE, &SyntacticalAnalyzer::checkFunctionIdentifier, std::nullopt, Error::ExpectedIdentifier),//18
			line(std::nullopt, &SyntacticalAnalyzer::checkEqualSymbol, std::nullopt, Error::ExpectedEqualSymbol),
			line(std::nullopt, &SyntacticalAnalyzer::checkConstant, std::nullopt, Error::ExpectedConstant),
			line(std::nullopt, FunctionCharacteristicE, true, std::nullopt),
			line(std::nullopt, &SyntacticalAnalyzer::checkSemicolon, true, Error::ExpectedSemicolon),
			line(FunctionCharacteristicE, &SyntacticalAnalyzer::checkDivisionSymbol, std::nullopt, Error::ExpectedDivisionSymbol),//23
			line(std::nullopt, &SyntacticalAnalyzer::checkUnsignedInteger, std::nullopt, Error::ExpectedUnsignedInteger),
			line(std::nullopt, &SyntacticalAnalyzer::checkComma, std::nullopt, Error::ExpectedComma),
			line(std::nullopt, &SyntacticalAnalyzer::checkUnsignedInteger, true, Error::ExpectedUnsignedInteger),
			line(StatementListE, &SyntacticalAnalyzer::checkEmptyStatementList, true, Error::ExpectedEmptyStatementList)//27

	});
	return table;
}


ErrorContext::ErrorContext(ErrorInKnutTable type)
	: m_error{ type }
	, m_info{}
{}

SyntacticalAnalyzer::SyntacticalAnalyzer(const Context& context, const TokensInfoVector& tokensInfoVector)
	: m_context{ context }
	, m_tokensInfoVector{ tokensInfoVector }
	, m_tree{ std::make_shared<Node>() }
	, m_table{ CreateTable() }
	, m_errorMap{ CreateErrorMap() }
{}
void SyntacticalAnalyzer::StartAnalyze()
{
	int start{ 0 };
	auto error = parse(0, start, m_tree.m_root);

	m_tree.Print(m_tree.m_root, 0);
	if (error)
	{
		writeError(*error);
	}
	
}
bool SyntacticalAnalyzer::isTerminal(const oneLine& lineInfo) const
{
	auto& [address, checker, AT, AF] = lineInfo;
	return checker.index() == 1;
}

bool SyntacticalAnalyzer::if_AT(int& currentLine, int& currentToken, NodePtr& node)
{
	auto& [address, checker, AT, AF] = (*m_table)[currentLine];
	if (AT)
	{
		if (AF && AF->m_error != ErrorInKnutTable::ExpectedEmptyStatementList)
		{
			++currentToken;
		}
		return true;
	}
	else
	{
		++currentLine;
		++currentToken;
		node->m_next = std::make_shared<Node>();
		node = node->m_next;
	}
	return false;
}
void SyntacticalAnalyzer::treeNextRoot(NodePtr& tmp, int currentLine)
{
	if (auto address = std::get<int>(GetSecondElement((*m_table)[currentLine]));
		address == FunctionE)
	{
		tmp = tmp->m_child->m_next;
		while (tmp->m_next)
		{
			tmp = tmp->m_next;
		}
		tmp->m_next = std::make_shared<Node>();
		tmp = tmp->m_next;
	}
	else
	{
		tmp = tmp->m_next = std::make_shared<Node>();
	}
}
void SyntacticalAnalyzer::writeError(const ErrorContext& context)
{
	auto errorInString = m_errorMap[context.m_error];
	std::cout << "\n\n"
		<< "Line: " << std::get<2>(context.m_info)
		<< ". Column: " << std::get<3>(context.m_info)
		<< "  " << errorInString << std::get<0>(context.m_info);
		     
}

std::optional<ErrorContext> SyntacticalAnalyzer::parse(int currentLine, int& currentToken, NodePtr& node)
{
	auto tmp = node;
	tmp->m_address = GetFirstElement((*m_table)[currentLine]);
	while (currentToken < m_tokensInfoVector.size())
	{
		while (!isTerminal((*m_table)[currentLine]))
		{
			tmp->m_child = std::make_shared<Node>();
			if (auto error = parse(std::get<int>(GetSecondElement((*m_table)[currentLine])), currentToken, tmp->m_child);
				error)
			{
				return error;
			}
			tmp = tmp->m_next = std::make_shared<Node>();
			++currentLine;
			if (currentToken >= m_tokensInfoVector.size())
			{
				return std::nullopt;
			}
		}
		do 
		{
			while (!isTerminal((*m_table)[currentLine]))
			{
				tmp->m_child = std::make_shared<Node>();
				if (auto error = parse(std::get<int>(GetSecondElement((*m_table)[currentLine])), currentToken, tmp->m_child);
					error)
				{
					return error;
				}
				treeNextRoot(tmp, currentLine);
				++currentLine;
				if (currentToken >= m_tokensInfoVector.size() || GetFirstElement((*m_table)[currentLine]) != std::nullopt)
				{
					return std::nullopt;
				}
			}
			auto& [address, checker, AT, AF] = (*m_table)[currentLine];
			auto& function = std::get<functionChecker>(checker);
			if ((this->*function)(m_tokensInfoVector, currentToken, tmp))
			{
				if (if_AT(currentLine, currentToken, tmp))
				{
					return std::nullopt;
				}
			}
			else
			{
				if (AF)
				{
					AF->m_info = m_tokensInfoVector[currentToken];
					return AF;
				}
				else
				{
					++currentLine;
				}
			}
		} while (currentToken < m_tokensInfoVector.size() && GetFirstElement((*m_table)[currentLine]) == std::nullopt);
	}
	return std::nullopt;
}
bool SyntacticalAnalyzer::checkProgram(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetKeywords();
    const auto it = keywords.find("PROGRAM");
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return it->second == tokenNumber;
}
bool SyntacticalAnalyzer::checkProcedureIdentifier(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetIdentifiers();
	node->m_address = ProcedureIdentifierE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    const auto it = keywords.find(tokenName);
    return it != keywords.end();
}
bool SyntacticalAnalyzer::checkFunctionIdentifier(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetIdentifiers();
	node->m_address = FunctionIdentifierE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    const auto it = keywords.find(tokenName);
    return it != keywords.end();
}

bool SyntacticalAnalyzer::checkSemicolon(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    node->m_token = tokens[currentToken];
	node->m_address = WriteE;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == ";";
}
bool SyntacticalAnalyzer::checkBegin(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetKeywords();
    const auto it = keywords.find("BEGIN");
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return it->second == tokenNumber;
}
bool SyntacticalAnalyzer::checkEnd(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetKeywords();
    const auto it = keywords.find("END");
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return it->second == tokenNumber;
}
bool SyntacticalAnalyzer::checkDot(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	node->m_address = WriteE;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    node->m_token = tokens[currentToken];
    return tokenName == ".";
}
bool SyntacticalAnalyzer::checkDeffunc(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetKeywords();
	node->m_address = WriteE;
    const auto it = keywords.find("DEFFUNC");
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return it->second == tokenNumber;
}
bool SyntacticalAnalyzer::checkEmptyMathFunctionDeclaration(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& keywords = m_context.GetKeywords();
    const auto it = keywords.find("DEFFUNC");
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
	return it->second != tokenNumber;
}

bool SyntacticalAnalyzer::checkEmptyFunctionList(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	const auto& keywords = m_context.GetIdentifiers();
	const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
	const auto it = keywords.find(tokenName);
	if (it == keywords.end())
	{
		node->m_address = EmptyFunctionListE;
		return true;
	}
	return false;
}
bool SyntacticalAnalyzer::checkEqualSymbol(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == "=";
}
bool SyntacticalAnalyzer::checkConstant(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    const auto& constant = m_context.GetConstants();
	node->m_address = ConstantE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    const auto it = constant.find(tokenName);
    return it != constant.end();
}
bool SyntacticalAnalyzer::checkDivisionSymbol(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == "\\";
}
bool SyntacticalAnalyzer::checkUnsignedInteger(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	node->m_address = UnsignedIntegerE;
    node->m_token = tokens[currentToken];
    const auto& constant = m_context.GetConstants();
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    const auto it = constant.find(tokenName);
    return it != constant.end();
}
bool SyntacticalAnalyzer::checkComma(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	node->m_address = WriteE;
    node->m_token = tokens[currentToken];
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return tokenName == ",";
}
bool SyntacticalAnalyzer::checkEmptyStatementList(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
	const auto& keywords = m_context.GetKeywords();
	const auto it = keywords.find("END");
	const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
	if( it->second == tokenNumber)
	{
		node->m_address = EmptyStatementListE;
		return true;
	}
	return false;
}
bool SyntacticalAnalyzer::checkEOF(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    return false;
}
