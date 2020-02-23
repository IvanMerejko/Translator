#include "Utils.h"
#include "TypesFmd.h"
#include "Constants.h"
#include "../Context.h"
#include "ParsingException.h"
#include "../TreeElements/Tree.h"

namespace utils
{

    SymbolsCategories CreateSymbolsCategories()
    {
        SymbolsCategories symbolsCategories
                {
                        /// Comment
                        {CharToInt('('), Categories::StartComment},
                        /// White space
                        {CharToInt(' '), Categories::WhiteSpace},
                        {CharToInt('\n'), Categories::WhiteSpace},
                        {8, Categories ::WhiteSpace}, //backspace
                        {9, Categories ::WhiteSpace}, //Tab
                        /// Digits
                        {CharToInt('0'), Categories::StartConstant},
                        {CharToInt('1'), Categories::StartConstant},
                        {CharToInt('2'), Categories::StartConstant},
                        {CharToInt('3'), Categories::StartConstant},
                        {CharToInt('4'), Categories::StartConstant},
                        {CharToInt('5'), Categories::StartConstant},
                        {CharToInt('6'), Categories::StartConstant},
                        {CharToInt('7'), Categories::StartConstant},
                        {CharToInt('8'), Categories::StartConstant},
                        {CharToInt('9'), Categories::StartConstant},
                        /// Upper Letters
                        {CharToInt('A'), Categories::StartIdentifier},
                        {CharToInt('B'), Categories::StartIdentifier},
                        {CharToInt('C'), Categories::StartIdentifier},
                        {CharToInt('D'), Categories::StartIdentifier},
                        {CharToInt('E'), Categories::StartIdentifier},
                        {CharToInt('F'), Categories::StartIdentifier},
                        {CharToInt('G'), Categories::StartIdentifier},
                        {CharToInt('H'), Categories::StartIdentifier},
                        {CharToInt('I'), Categories::StartIdentifier},
                        {CharToInt('J'), Categories::StartIdentifier},
                        {CharToInt('K'), Categories::StartIdentifier},
                        {CharToInt('L'), Categories::StartIdentifier},
                        {CharToInt('M'), Categories::StartIdentifier},
                        {CharToInt('N'), Categories::StartIdentifier},
                        {CharToInt('O'), Categories::StartIdentifier},
                        {CharToInt('P'), Categories::StartIdentifier},
                        {CharToInt('R'), Categories::StartIdentifier},
                        {CharToInt('S'), Categories::StartIdentifier},
                        {CharToInt('T'), Categories::StartIdentifier},
                        {CharToInt('U'), Categories::StartIdentifier},
                        {CharToInt('V'), Categories::StartIdentifier},
                        {CharToInt('W'), Categories::StartIdentifier},
                        {CharToInt('X'), Categories::StartIdentifier},
                        {CharToInt('Y'), Categories::StartIdentifier},
                        {CharToInt('Z'), Categories::StartIdentifier},
                        /// Small Letters
                        {CharToInt('a'), Categories::StartIdentifier},
                        {CharToInt('b'), Categories::StartIdentifier},
                        {CharToInt('c'), Categories::StartIdentifier},
                        {CharToInt('d'), Categories::StartIdentifier},
                        {CharToInt('e'), Categories::StartIdentifier},
                        {CharToInt('f'), Categories::StartIdentifier},
                        {CharToInt('g'), Categories::StartIdentifier},
                        {CharToInt('h'), Categories::StartIdentifier},
                        {CharToInt('i'), Categories::StartIdentifier},
                        {CharToInt('j'), Categories::StartIdentifier},
                        {CharToInt('k'), Categories::StartIdentifier},
                        {CharToInt('l'), Categories::StartIdentifier},
                        {CharToInt('m'), Categories::StartIdentifier},
                        {CharToInt('n'), Categories::StartIdentifier},
                        {CharToInt('o'), Categories::StartIdentifier},
                        {CharToInt('p'), Categories::StartIdentifier},
                        {CharToInt('r'), Categories::StartIdentifier},
                        {CharToInt('s'), Categories::StartIdentifier},
                        {CharToInt('t'), Categories::StartIdentifier},
                        {CharToInt('u'), Categories::StartIdentifier},
                        {CharToInt('v'), Categories::StartIdentifier},
                        {CharToInt('w'), Categories::StartIdentifier},
                        {CharToInt('x'), Categories::StartIdentifier},
                        {CharToInt('y'), Categories::StartIdentifier},
                        {CharToInt('z'), Categories::StartIdentifier},
                        /// one symbol delimiter
                        {CharToInt('='),  Categories::OneSymbolSeparator},
                        {CharToInt(';'),  Categories::OneSymbolSeparator},
                        {CharToInt(','),  Categories::OneSymbolSeparator},
                        {CharToInt('.'),  Categories::OneSymbolSeparator},
                        {CharToInt('\\'), Categories::OneSymbolSeparator},

                        {CharToInt('\r'), Categories::ScipSymbol},
                        {CharToInt('\000'), Categories::ScipSymbol},
                };
        return symbolsCategories;
    }



    TokenNameToCodeMap CreateKeywordsMap()
    {
        auto start = KeywordsNumberStart;
        TokenNameToCodeMap map
                {
                        {ProgramString, ++start},
                        {DeffuncString, ++start},
                        {BeginString, ++start},
                        {EndString, ++start}
                };
        return map;
    }

    Categories GetSymbolCategories(Symbol symbol, const Context& context)
    {
        const auto& symbolsCategories = context.GetSymbolsCategories();
        const auto it = symbolsCategories.find(CharToInt(symbol));
        if(it != symbolsCategories.end())
        {
            return it->second;
        }
        return Categories::ErrorSymbol;
    }

    TokenNumber AddNewIdentifierIfNotExist(TokenView name, TokenNameToCodeMap& identifiers)
    {
        static auto number = IdentifiersNumberStart;
        const auto it = identifiers.find(name.data());
        if(it != identifiers.end())
        {
            return it->second;
        }
        identifiers.insert({name.data(), ++number});
        return number;
    }

    TokenNumber AddNewConstantIfNotExist(TokenView name, TokenNameToCodeMap& constants)
    {
        static auto number = ConstantsNumberStart;
        const auto it = constants.find(name.data());
        if(it != constants.end())
        {
            return it->second;
        }
        constants.insert({name.data(), ++number});
        return number;
    }
    void PrintSeparator(int step)
    {
        for(int i = 0 ; i < step ; ++i)
        {
            std::cout << "_ ";
        }
    }
    void PrintProcedureIdentifier(int count, TokenNumber number,const TokenName& name)
    {
        PrintSeparator(count+3);
        std::cout << "<procedure-identifier>\n";
        PrintIdentifier(count + 3, number, name);
    }
    void PrintFunctionIdentifier(int count, TokenNumber number,const TokenName& name)
    {
        PrintSeparator(count);
        std::cout << "<function-identifier>\n";
        PrintIdentifier(count, number, name);
    }
    void PrintIdentifier(int count, TokenNumber number,const TokenName& name)
    {
        PrintSeparator(count+3);
        std::cout << "<identifier>\n";
        PrintSeparator(count+6);
        std::cout << number << " " << name << "\n";
    }
    void PrintEmpty(int count)
    {
        PrintSeparator(count);
        std::cout << "<empty>\n";
    }
    void PrintUnsignedInteger(int count, TokenNumber number,const TokenName& name)
    {
        PrintSeparator(count);
        std::cout << "<unsigned-integer>\n";
        PrintSeparator(count+3);
        std::cout << number << " " << name << "\n";
    }
    void PrintConstant(int count, TokenNumber number,const TokenName& name)
    {
        PrintSeparator(count);
        std::cout << "<constant>\n";
        PrintUnsignedInteger(count + 3, number, name);
    }
    void ThrowException(const std::string& text, const TokensInfoVector& tokens, int currentToken)
    {
        const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
        throw ParsingException(text, line, column, tokenName);
    }
	int SpecialPrint(Address currentAddress, int count, NodePtr& node)
	{
		switch (currentAddress)
		{
		case SignalProgramE:
			std::cout << "<signal-program>\n";
			count += 3;
			PrintSeparator(count);
			std::cout << "<program>\n";
			break;
		case ProgramE:
			std::cout << "<program>\n";
			break;
		case BlockE:
			std::cout << "<block>\n";
			break;
		case DeclarationsE:
			std::cout << "<declarations>\n";
			count += 3;
			if (node->m_child && *node->m_child->m_address != MathFunctionDeclarationE)
			{
				PrintSeparator(count);
				std::cout << "<math-function-declaration>\n";
			}
			break;
		case MathFunctionDeclarationE:
			std::cout << "<math-function-declaration>\n";
			PrintEmpty(count + 3);
			break;
		case FunctionListE:
			std::cout << "<function-list>\n";
			break;
		case FunctionE:
			std::cout << "<function>\n";
			break;
		case FunctionCharacteristicE:
			std::cout << "<function-characteristic>\n";
			break;
		case StatementListE:
			std::cout << "<statement-list>\n";
			break;
		case ProcedureIdentifierE:
			std::cout << "<procedure-identifier>\n";
			PrintSeparator(count + 3);
			std::cout << std::get<1>(node->m_token) << " "
				<< std::get<0>(node->m_token) << "\n";
			break;
		case WriteE:
			break;
		case FunctionIdentifierE:
			std::cout << "<function-identifier>\n";
			PrintSeparator(count + 3);
			std::cout << std::get<1>(node->m_token) << " "
				<< std::get<0>(node->m_token) << "\n";
			break;
		case ConstantE:
			std::cout << "<constant>\n";
			PrintSeparator(count + 3);
			std::cout << std::get<1>(node->m_token) << " "
				<< std::get<0>(node->m_token) << "\n";
			PrintSeparator(count);
			std::cout << "<function-characteristic>\n";
			count += 3;
			break;
		case UnsignedIntegerE:
			std::cout << "<unsigned-integer>\n";
			PrintSeparator(count + 3);
			std::cout << std::get<1>(node->m_token) << " "
				<< std::get<0>(node->m_token) << "\n";
			break;
		case EmptyFunctionListE:
			std::cout << "<function-list>\n";
			PrintEmpty(count + 3);
			break;
		case EmptyStatementListE:
			std::cout << "<statement-list>\n";
			PrintEmpty(count + 3);
			break;
		case EmptyMathFunctionDeclarationE:
			std::cout << "<math-function-declaration>\n";
			PrintEmpty(count + 3);
			break;
		default:
			break;
		}
		return count;
	}
}

