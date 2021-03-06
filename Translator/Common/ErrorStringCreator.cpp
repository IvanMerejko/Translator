
#include "ErrorStringCreator.h"
#include "Constants.h"

std::string ErrorStringCreator::createErrorStringOfIncorrectSymbol(Symbol name, TokenLine line, TokenColumn column)
{
    std::string text = LineString;
    text.append(std::to_string(line))
            .append(ColumnString)
            .append(std::to_string(column))
            .append(ErrorString)
            .append(IncorrectSymbolString)
            .append(1, name);
    return text;
}

std::string ErrorStringCreator::createErrorStringOfUnclosedComment(TokenLine line, TokenColumn column)
{
    std::string text = LineString;
    text.append(std::to_string(line))
            .append(ColumnString)
            .append(std::to_string(column))
            .append(ErrorString)
            .append(UnclosedCommentString);
    return text;
}

std::string ErrorStringCreator::createErrorStringOfIncorrectSymbolAfterConstant(Symbol symbol,
    TokenLine line, TokenColumn column)
{
    std::string text = LineString;
    text.append(std::to_string(line))
            .append(ColumnString)
            .append(std::to_string(column))
            .append(ErrorString)
            .append(IncorrectSymbolAfterConstantString)
            .append(1, symbol)
            .append(MustBeSpaceString);
    return text;
}

std::string ErrorStringCreator::createErrorStringOfIncorrectSymbolAfterIdentifier(Symbol symbol,
    TokenLine line, TokenColumn column)
{
    std::string text = LineString;
    text.append(std::to_string(line))
            .append(ColumnString)
            .append(std::to_string(column))
            .append(ErrorString)
            .append(IncorrectSymbolAfterIdentifierString)
            .append(1, symbol)
            .append(MustBeSpaceString);
    return text;
}

std::string ErrorStringCreator::createErrorStringOfErrorInSharpText(ParsingState state, TokenLine line, TokenColumn column)
{
    std::string text = LineString;
    auto error = state == ParsingState::ErrorInParsingSharpTextMustBeLetter ? MustBeLetterString :
                 state == ParsingState::ErrorInParsingSharpTextMustBeDigit  ? MustBeDigitString :
                 state == ParsingState::ErrorInParsingSharpTextMustBePlus ? MustBePlusString : MustBeStarString;
    text.append(std::to_string(line))
            .append(ColumnString)
            .append(std::to_string(column))
            .append(ErrorString)
            .append(error);
    return text;
}