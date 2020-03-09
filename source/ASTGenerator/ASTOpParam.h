#pragma once
#include "ASTNode.h"

class ASTOpParam : public ASTNode
{
public:
    ASTOpParam(unsigned int t_referenceLine) : ASTNode(t_referenceLine)
    {}
};