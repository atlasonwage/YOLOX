#pragma once
#include "ASTNode.h"
#include "ASTVar.h"

//Implements a variable operation
class ASTOp : public ASTNode
{
public:
    enum class Op {
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
    const Op op;
    ASTVar * const pLeft;
    ASTVar * const pRight;

    ASTBinary();
    ~ASTBinary();
    virtual std::string process() const override;
};