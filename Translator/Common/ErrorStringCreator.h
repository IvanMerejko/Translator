#pragma once

#include "TypesFmd.h"
class ErrorStringCreator
{
public:
    static std::string createErrorStringOfIncorrectSymbol(Symbol name, TokenLine line, TokenColumn column);
    static std::string createErrorStringOfUnclosedComment(TokenLine line, TokenColumn column);
    static std::string createErrorStringOfIncorrectSymbolAfterConstant(Symbol symbol,
            TokenLine line, TokenColumn column);
    static std::string createErrorStringOfIncorrectSymbolAfterIdentifier(Symbol symbol,
            TokenLine line, TokenColumn column);
};



