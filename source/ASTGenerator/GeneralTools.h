#pragma once
#include <string>

constexpr unsigned int MAX_LINE_LENGTH = 70;
constexpr unsigned int RESERVED_GOTO_LENGTH = 4;

//Optimization parameters
constexpr unsigned int CONDITIONAL_LENGTH = 14;
constexpr unsigned int ELSE_CONDITIONAL_LENGTH = CONDITIONAL_LENGTH + 5;
constexpr unsigned int GOTO_SKIP_LENGTH = CONDITIONAL_LENGTH + 6 + RESERVED_GOTO_LENGTH;

enum class IdentifierOptimizationLevel {NONE, LOW, HIGH};

extern IdentifierOptimizationLevel varOptimizationLevel;
extern IdentifierOptimizationLevel fieldOptimizationLevel;

unsigned int linesInString(const std::string& t_rString);
unsigned int lastLineLength(const std::string& t_rString);