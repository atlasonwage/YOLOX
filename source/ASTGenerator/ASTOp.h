#pragma once
#include "ASTVar.h"

//Implements a variable operation
class ASTOp : public ASTOpParam
{
public:
    static enum Op {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        EXP,
        PRE_INC,
        POST_INC,
        PRE_DEC,
        POST_DEC,
        ASSIGN,
        ADD_ASSIGN,
        SUB_ASSIGN,
        MUL_ASSIGN,
        DIV_ASSIGN,
        MOD_ASSIGN,
        EXP_ASSIGN,
        ABS,
        FACT,
        SQRT,
        SIN,
        COS,
        TAN,
        ASIN,
        ACOS,
        ATAN
    };

    ASTOp(unsigned int t_referenceLine, const Op t_op, 
        ASTOpParam * const t_pLeft, ASTOpParam * const t_pRight = nullptr);
    ~ASTOp();
    virtual std::string process() const override;
private:
    static std::string opString(const Op t_op);

    Op m_op;
    ASTOpParam * m_pLeft;
    ASTOpParam * m_pRight;
};