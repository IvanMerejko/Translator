//
// Created by Ivan on 12.02.2020.
//

#include "SyntacticalAnalyzer.h"
#include "Common/ParsingException.h"
#include <utility>
#include <array>

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
{}
void SyntacticalAnalyzer::StartAnalyze()
{
	int start{ 0 };
	if (auto error = parse(0, start, m_tree.m_root))
	{
		std::cout << "\n" << std::get<0>(error->m_info) << '\n';
	}
	m_tree.Print(m_tree.m_root, 0);
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
		if (AF)
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
				tmp = tmp->m_next = std::make_shared<Node>();
				++currentLine;
				if (GetFirstElement((*m_table)[currentLine]) != std::nullopt)
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
	return it == keywords.end();
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
	return it->second == tokenNumber;
}
bool SyntacticalAnalyzer::checkEOF(const TokensInfoVector& tokens, int& currentToken, NodePtr& node) const
{
    return false;
}



/*std::optional<ErrorContext> SyntacticalAnalyzer::parse(int currentLine, int& currentToken, NodePtr& node)
{
	auto tmp = node;
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
				tmp = tmp->m_next = std::make_shared<Node>();
				++currentLine;
				if (GetFirstElement((*m_table)[currentLine]) != std::nullopt)
				{
					return std::nullopt;
				}
			}
			
			auto& [address, checker, AT, AF] = (*m_table)[currentLine];
			auto& function = std::get<functionChecker>(checker);
			if ((this->*function)(m_tokensInfoVector, currentToken, tmp))
			{
			if (AT)
			{
				if (AF)
				{
					++currentToken;
				}
				return std::nullopt;
			}
			else
			{
				++currentLine;
				++currentToken;
				tmp->m_next = std::make_shared<Node>();
				tmp = tmp->m_next;
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
			}*/