#pragma once
#include "ASTNode.h"
#include "TypeService.h"

class ASTOpParam : public ASTNode
{
public:
    ASTOpParam(unsigned int t_referenceLine) : ASTNode(t_referenceLine)
    {}

    virtual TID getType() const = 0;
};