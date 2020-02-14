#include "Context.h"
#include "Common\Utils.h"

Context::Context()
    : m_symbolCategories{utils::CreateSymbolsCategories()}
    , m_keywords{utils::CreateKeywordsMap()}
    , m_identifiers{}
    , m_constants{}
{}

const SymbolsCategories& Context::GetSymbolsCategories() const noexcept
{
    return m_symbolCategories;
}
const TokenNameToCodeMap& Context::GetKeywords() const noexcept
{
    return m_keywords;
}

const TokenNameToCodeMap& Context::GetIdentifiers() const  noexcept
{
    return m_identifiers;
}

const TokenNameToCodeMap& Context::GetConstants() const  noexcept
{
    return m_constants;
}

TokenNumber Context::AddNewIdentifierIfNotExist(TokenView name)
{
    return utils::AddNewIdentifierIfNotExist(name, m_identifiers);
}

TokenNumber Context::AddNewConstantIfNotExist(TokenView name)
{
    return utils::AddNewConstantIfNotExist(name, m_constants);
}