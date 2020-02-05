//
// Created by ivanm on 2/5/2020.
//

#include "Comment.h"
#include "BaseElement.h"
#include "../Common/Utils.h"

Comment::Comment(const Context& context)
    :BaseElement{context}
{}
/*
 * We already parsed comment begin symbols in LexicalAnalyzer, so we need
 * only to find end of comment
 *
 * */
OptionalSymbol Comment::ParseElement(std::iostream& file)
{
    Symbol currentSymbol{};
    bool isSymbolBeginningOfEndOfCommentAlreadyExists {false};
    while ( file.get(currentSymbol))
    {
        if( isBeginningEndComment(currentSymbol))
        {
            isSymbolBeginningOfEndOfCommentAlreadyExists = true;
        }
        else if(isSymbolBeginningOfEndOfCommentAlreadyExists &&
            isBeginningEndComment(currentSymbol))
        {
            return std::nullopt;
        }
        else
        {
            isSymbolBeginningOfEndOfCommentAlreadyExists = false;
        }

    }
    m_parsingState = ParsingState::Error;
    return EOF;
}
SymbolsString Comment::GetParsedElementInString() const noexcept
{
    return {};
}

bool Comment::isBeginningEndComment(Symbol symbol) const noexcept
{
    return symbol == '*';
}

bool Comment::isEndOfComment(Symbol symbol) const noexcept
{
    return symbol == '/';
}

ParsingState Comment::GetElementParsingState() const noexcept
{
    return m_parsingState;
}