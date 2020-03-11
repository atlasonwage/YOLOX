#pragma once
#include <string>

void verifyCorrectOutput(const std::string& t_name,
    const std::string t_output, const std::string t_expected, const bool t_verbose);

//ASTBlock
std::string block();   //Verifies the functionality of process and merge
std::string block_expected();