#pragma once
#include "ASTOpParam.h"

class ASTBool : public ASTOpParam
{
public:
    ASTBool(unsigned int t_referenceLine) : ASTOpParam(t_referenceLine)
    {}

    virtual void inverse() = 0;
    virtual void isInversed() = 0;
};