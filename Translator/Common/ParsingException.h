#pragma once
#include "TypesFmd.h"

#include <iostream>
#include <exception>
#include <string>

class ParsingException : public std::exception
{
public:
    ParsingException(std::string text, TokenLine line, TokenColumn column, const TokenName& name);
    const char* what() const noexcept override;

private:
    std::string m_text;
    TokenLine m_line;
    TokenColumn m_column;
    TokenName m_name;
};
