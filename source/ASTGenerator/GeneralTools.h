#pragma once

constexpr unsigned int MAX_LINE_LENGTH = 70;
constexpr unsigned int RESERVED_GOTO_LENGTH = 4;

void throwError(const std::string t_message, const unsigned int t_lineNum);

unsigned int linesInString(const std::string& t_rString);