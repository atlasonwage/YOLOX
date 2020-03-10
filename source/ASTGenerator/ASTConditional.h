#pragma once
#include "ASTBool.h"

//Implements a conditional.
//Conditionals have line priority.
class ASTConditional : public ASTNode
{
public:
    ASTConditional(unsigned int t_referenceLine, ASTBool * const t_pConditional, 
        ASTNode * const t_pTrue, ASTNode * const t_pFalse = nullptr);
    ~ASTConditional();

    virtual std::string process() const override;
private:
    ASTBool * const m_pConditional;
    ASTNode * const m_pTrue;
    ASTNode * const m_pFalse;
};