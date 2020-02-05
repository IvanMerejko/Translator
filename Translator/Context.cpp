//
// Created by ivanm on 2/5/2020.
//

#include "Context.h"
#include "Common\Utils.h"

Context::Context()
    : m_symbolCategories{CreateSymbolsCategories()}
    , m_keywords{CreateIdentifiersMap()}
    , m_identifiers{}
{}

const SymbolsCategories& Context::GetSymbolsCategories() noexcept
{
    return m_symbolCategories;
}
const NameToCodeMap& Context::GetKeywords() noexcept
{
    return m_keywords;
}
const NameToCodeMap& Context::GetIdentifiers() noexcept
{
    return m_identifiers;
}