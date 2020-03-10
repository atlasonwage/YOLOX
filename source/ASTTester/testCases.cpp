#include "testCases.h"
#include <iostream>

#include "ASTDummy.h"
#include "../ASTGenerator/ASTBlock.h"

void block_merge()
{

}

//Push these strings: 70, 10*, 30, 30, 30
//                    a   b    c   d   e
//Expected: a \n b \n c d \n e
//* indicates line priority
void block_process()
{
    std::string str;
    for (unsigned int i = 0; i < 70; ++i)
    {
        str[i] = 'a';
    }
    ASTDummy * pA = new ASTDummy(0, str);

    for (unsigned int i = 0; i < 10; ++i)
    {
        str[i] = 'b';
    }
    ASTDummy * pB = new ASTDummy(0, str, true);

    for (unsigned int i = 0; i < 30; ++i)
    {
        str[i] = 'c';
    }
    ASTDummy * pC = new ASTDummy(0, str);

    for (unsigned int i = 0; i < 30; ++i)
    {
        str[i] = 'd';
    }
    ASTDummy * pD = new ASTDummy(0, str);

    for (unsigned int i = 0; i < 30; ++i)
    {
        str[i] = 'e';
    }
    ASTDummy * pE = new ASTDummy(0, str);


    ASTBlock block(0);

    block.addChild(pA);
    block.addChild(pB);
    block.addChild(pC);
    block.addChild(pD);
    block.addChild(pE);

    std::cout << block.process() << std::endl;
}