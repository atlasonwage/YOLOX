#include "testCases.h"
#include <cstring>
#include <iostream>

int main(int argc, char * argv[])
{
    bool verbose = false;
    if (argc == 2 && strcmp(argv[1], "-v") == 0)
    {
        verbose = true;
    }

    verifyCorrectOutput(std::string("ASTBlock"), block(), block_expected(), verbose);
}