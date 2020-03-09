#pragma once
#include <string>
#include "GeneralTools.h"

//Basic building block of AST trees.
//Memory is automatically cleaned up from dyamically-allocated nodes.
class ASTNode
{
public:
    unsigned int LINE_NUM;
    //Processes the children and this node.
    virtual std::string process() const = 0;

    ASTNode(unsigned int t_referenceLineNumber) : LINE_NUMBER (t_referenceLineNumber)
    {}
};