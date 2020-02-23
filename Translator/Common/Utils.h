#pragma once

#include <iostream>
#include "TypesFmd.h"
#include "../Context.h"
#include "../TreeElements/Tree.h"

namespace utils
{
    constexpr auto CharToInt(char value)
    {
        return static_cast<int>(value);
    }

    SymbolsCategories CreateSymbolsCategories();

    TokenNameToCodeMap CreateKeywordsMap();

    TokenNumber AddNewIdentifierIfNotExist(TokenView name, TokenNameToCodeMap& identifiers);
    TokenNumber AddNewConstantIfNotExist(TokenView name, TokenNameToCodeMap& constants);

    Categories GetSymbolCategories(Symbol symbol, const Context& context);

    constexpr auto incrementLineIfNeed(Symbol symbol, TokenLine& line, TokenColumn& column)
    {
        if (symbol == '\n')
        {
            ++line;
            column = 1;
            return true;
        }
        return false;
    }

    constexpr auto IsSpace(Symbol symbol)
    {
        return symbol == ' ' || symbol == '\n' || symbol == '\r';
    }
    void PrintSeparator(int step);
    void PrintProcedureIdentifier(int count, TokenNumber number,const TokenName& name);
    void PrintFunctionIdentifier(int count, TokenNumber number,const TokenName& name);
    void PrintIdentifier(int count, TokenNumber number,const TokenName& name);
    void PrintConstant(int count, TokenNumber number,const TokenName& name);
    void PrintUnsignedInteger(int count, TokenNumber number,const TokenName& name);
    void PrintEmpty(int count);
    void ThrowException(const std::string& text, const TokensInfoVector& tokens, int currentToken);
	int SpecialPrint(Address currentAddress, int count, NodePtr& node);
}



