//
// Created by Ivan on 12.02.2020.
//

#include "StatementList.h"
#include "../Common/Constants.h"


StatementList::StatementList(const Context& context)
    : BaseTreeElement{context}
{}

void StatementList::operator() (const TokensInfoVector& tokens, int& currentToken)
{
    if(!isEmpty(tokens, currentToken))
    {
        utils::ThrowException(" Statement list must be empty. ", tokens, currentToken);
    }
}
void StatementList::Print(int count)
{
    utils::PrintSeparator(count);
    std::cout << "<statement-list>\n";
    utils::PrintEmpty(count+3);
}


bool StatementList::isEmpty(const TokensInfoVector& tokens, int& currentToken)
{
    const auto& keywords = m_context.GetKeywords();
    const auto& number = keywords.find(EndString)->second;
    const auto& [tokenName, tokenNumber, line, column] = tokens[currentToken];
    return number == tokenNumber;
}