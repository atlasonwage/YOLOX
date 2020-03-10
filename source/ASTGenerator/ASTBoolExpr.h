#pragma once
#include "ASTBool.h"

//Implements a boolean logic expression
class ASTBoolExpr : public ASTBool
{
public:
    enum Op : unsigned int {
        LTHN,
        LTHNEQ,
        GTHN,
        GTHNEQ,
        EQUAL,
        NEQUAL,
        AND,
        OR,
        NAND,
        NOR
    };
    
    
    ASTBool * const pLeft;
    ASTBool * const pRight;

    ASTBoolExpr(unsigned int t_referenceLine, const Op t_op, 
        ASTBool * const t_pLeft, ASTBool * const t_pRight = nullptr);
    ~ASTBoolExpr();
    virtual std::string process() const override;

    virtual void inverse() override;
    virtual bool isInversed() const override;
protected:
    Op m_op;
private:
    bool demorganFlip() const;
    std::string orderHandle(ASTBool * const t_pBool) const;
};