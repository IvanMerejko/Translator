//
// Created by ivanm on 2/5/2020.
//

#include "Context.h"
#include "Common\Utils.h"

Context::Context()
    : m_symbolCategories{CreateSymbolsCategories()}
    , m_keywords{CreateKeywordsMap()}
    , m_identifiers{}
{}

const SymbolsCategories& Context::GetSymbolsCategories()const& noexcept
{
    return m_symbolCategories;
}
const NameToCodeMap& Context::GetKeywords()const& noexcept
{
    return m_keywords;
}
const NameToCodeMap& Context::GetIdentifiers()const&  noexcept
{
    return m_identifiers;
}