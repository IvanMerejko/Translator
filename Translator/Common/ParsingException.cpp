//
// Created by Ivan on 15.02.2020.
//

#include "ParsingException.h"
#include "Constants.h"


ParsingException::ParsingException(std::string text, TokenLine line, TokenColumn column, const TokenName& name)
    : m_text{std::move(text)}
    , m_line{line}
    , m_column{column}
    , m_name{name}
{}
const char* ParsingException::what() const noexcept
{
    std::string result = LineString;
    result.append(std::to_string(m_line))
            .append(ColumnString)
            .append(std::to_string(m_column))
            .append(ErrorString)
            .append(m_text)
            .append(" Found: ")
            .append(m_name);
    return result.data();
}