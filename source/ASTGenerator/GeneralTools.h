#pragma once

constexpr unsigned int MAX_LINE_LENGTH = 70;
constexpr unsigned int RESERVED_GOTO_LENGTH = 4;

//Optimization parameters
constexpr unsigned int CONDITIONAL_LENGTH = 14;
constexpr unsigned int ELSE_CONDITIONAL_LENGTH = CONDITIONAL_LENGTH + 5;
constexpr unsigned int GOTO_SKIP_LENGTH = CONDITIONAL_LENGTH + 6 + RESERVED_GOTO_LENGTH;

//Throws and error and stops the program from compiling.
//Other tree routes can be explored to find other errors to fix.
void throwError(const std::string t_message, const unsigned int t_lineNum);

unsigned int linesInString(const std::string& t_rString);
unsigned int lastLineLength(const std::string& t_rString);