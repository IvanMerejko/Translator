//
// Created by ivanm on 2/5/2020.
//

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

const TokenNameToCodeMap& Context::GetConstants() const  noexcept
{
    return m_constants;
}

TokenNumber Context::AddNewIdentifier(TokenView name)
{
    return utils::AddNewIdentifier(name, m_identifiers);
}

TokenNumber Context::AddNewConstant(TokenView name)
{
    return utils::AddNewConstant(name, m_constants);
}