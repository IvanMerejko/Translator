#pragma once


#include "Common/TypesFmd.h"

class Context
{
public:
    Context();

    const SymbolsCategories& GetSymbolsCategories() const noexcept;
    const NameToCodeMap& GetKeywords() const noexcept;
    const NameToCodeMap& GetIdentifiers() const noexcept;
private:
    SymbolsCategories m_symbolCategories;
    NameToCodeMap m_keywords;
    NameToCodeMap m_identifiers;
};



