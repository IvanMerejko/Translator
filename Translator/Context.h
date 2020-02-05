#pragma once


#include "Common/TypesFmd.h"

class Context
{
public:
    Context();

    const SymbolsCategories& GetSymbolsCategories() noexcept;
    const NameToCodeMap& GetKeywords() noexcept;
    const NameToCodeMap& GetIdentifiers() noexcept;
private:
    SymbolsCategories m_symbolCategories;
    NameToCodeMap m_keywords;
    NameToCodeMap m_identifiers;
};



