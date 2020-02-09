#pragma once


#include "Common/TypesFmd.h"

class Context
{
public:
    Context();

    const SymbolsCategories& GetSymbolsCategories() const noexcept;
    const TokenNameToCodeMap& GetKeywords() const noexcept;
    const TokenNameToCodeMap& GetIdentifiers() const noexcept;
    const TokenNameToCodeMap& GetConstants() const noexcept;
    TokenNumber AddNewIdentifierIfNotExist(TokenView name);
    TokenNumber AddNewConstantIfNotExist(TokenView name);
private:
    SymbolsCategories m_symbolCategories;
    TokenNameToCodeMap m_keywords;
    TokenNameToCodeMap m_identifiers;
    TokenNameToCodeMap m_constants;
};



