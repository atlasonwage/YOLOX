#include "testCases.h"
#include <iostream>

#include "ASTDummy.h"
#include <ASTBlock.h>

void verifyCorrectOutput(const std::string& t_name,
    const std::string t_output, const std::string t_expected, const bool t_verbose)
{
    std::cout << t_name << ": ";
    if (t_output == t_expected)
    {
        std::cout << "PASSED\n";
    } else {
        std::cout << "FAILED\n";
        if (t_verbose)
        {
            std::cout << "Function Return:\n" << t_output;
            std::cout << "\n\nExpected:\n" << t_expected;
            std::cout << "\n\n";
        }
    }
}


std::string block_expected()
{
    return std::string( "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
                        "bbbbbbbbbb\n"
                        "cccccccccccccccccccccccccccccc dddddddddddddddddddddddddddddd\n"
                        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
                        "bbbbbbbbbb\n"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
                        "bbbbbbbbbb\n"
                        "cccccccccccccccccccccccccccccc dddddddddddddddddddddddddddddd\n"
                        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
}
//Push these strings: 70, 10*, 30, 30, 30
//                    a   b    c   d   e
//Expected: a \n b \n c d \n e \n
//          b \n a \n b \n c d \n e
//* indicates line priority
std::string block()
{
    std::string rStr;
    std::string str;
    for (unsigned int i = 0; i < 70; ++i)
    {
        str.push_back('a');
    }
    ASTDummy * pA = new ASTDummy(0, str);

    str.clear();
    for (unsigned int i = 0; i < 10; ++i)
    {
        str.push_back('b');
    }
    ASTDummy * pB = new ASTDummy(0, str, true);
    ASTDummy * pB2 = new ASTDummy(0, str, true);

    str.clear();
    for (unsigned int i = 0; i < 30; ++i)
    {
        str.push_back('c');
    }
    ASTDummy * pC = new ASTDummy(0, str);

    str.clear();
    for (unsigned int i = 0; i < 30; ++i)
    {
        str.push_back('d');
    }
    ASTDummy * pD = new ASTDummy(0, str);

    str.clear();
    for (unsigned int i = 0; i < 30; ++i)
    {
        str.push_back('e');
    }
    ASTDummy * pE = new ASTDummy(0, str);


    ASTBlock * pBlock = new ASTBlock(0);
    ASTBlock block(1);

    pBlock->addChild(pA);
    pBlock->addChild(pB);
    pBlock->addChild(pC);
    pBlock->addChild(pD);
    pBlock->addChild(pE);

    block.addChild(pB2);

    rStr += pBlock->process() + "\n";

    //Tests merging.
    block.addChild(pBlock);
    
    rStr += block.process();
    return rStr;
}