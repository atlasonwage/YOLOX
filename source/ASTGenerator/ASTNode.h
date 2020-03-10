#pragma once
#include <string>
#include "GeneralTools.h"

//Basic building block of AST trees.
//Memory is automatically cleaned up from dyamically-allocated nodes.
class ASTNode
{
public:
    const unsigned int LINE_NUM;
    //Processes the children and this node.
    virtual std::string process() const = 0;

    //Nodes with line priority will not be in-line with other text.
    const bool m_linePriority;

    ASTNode(unsigned int t_referenceLineNumber, bool t_linePriority = false) :
        LINE_NUM (t_referenceLineNumber), m_linePriority(t_linePriority)
    {}
};