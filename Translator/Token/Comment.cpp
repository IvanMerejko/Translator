#include "Comment.h"
#include "BaseElement.h"
#include "../Common/Utils.h"
#include <iostream>
#include <fstream>
Comment::Comment(const Context& context)
    :BaseElement{context}
{}
/*
 * We already parsed comment begin symbols in LexicalAnalyzer, so we need
 * only to find end of comment
 *
 * */
Symbol Comment::ParseElement(std::ifstream& file, TokenLine& line, TokenColumn& column)
{
    Symbol currentSymbol{};
    bool isSymbolBeginningOfEndOfCommentAlreadyExists {false};
    while ( file.get(currentSymbol))
    {
        ++column;
        if( isBeginningEndComment(currentSymbol))
        {
            isSymbolBeginningOfEndOfCommentAlreadyExists = true;
        }
        else if(isSymbolBeginningOfEndOfCommentAlreadyExists &&
                isEndOfComment(currentSymbol))
        {
            file.get(currentSymbol);
            ++column;
            return currentSymbol;
        }
        else
        {
            isSymbolBeginningOfEndOfCommentAlreadyExists = false;
        }
        if(utils::incrementLineIfNeed(currentSymbol, line, column))
        {
            --column;
        }
    }
    m_parsingState = ParsingState::ErrorUnclosedComment;
    return EOF;
}
OptionalSymbolsString Comment::GetParsedElementInString() const noexcept
{
    return std::nullopt;
}

bool Comment::isBeginningEndComment(Symbol symbol) const noexcept
{
    return symbol == '*';
}

bool Comment::isEndOfComment(Symbol symbol) const noexcept
{
    return symbol == ')';
}

ParsingState Comment::GetElementParsingState() const noexcept
{
    return m_parsingState;
}