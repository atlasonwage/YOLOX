#include "ASTBoolExpr.h"

ASTBoolExpr::ASTBoolExpr(unsigned int t_referenceLine, const Op t_op, 
    ASTBool * const t_pLeft, ASTBool * const t_pRight) :
    ASTBool(t_referenceLine), m_op(t_op), 
    pLeft(t_pLeft), pRight(t_pRight)
{
    if (pLeft->isInversed() && pRight->isInversed())
    {
        pLeft->inverse();
        pRight->inverse();
        switch(t_op)
        {
            case AND:
                m_op = NOR;
                break;
            case OR:
                m_op = NAND;
                break;
            case NAND:
                m_op = OR;
                break;
            case NOR:
                m_op = AND;
                break;
        }
    }
    
}

ASTBoolExpr::~ASTBoolExpr()
{
    delete pLeft;
    delete pRight;
}


//May add order-of-operations in the future for better optimization
std::string ASTBoolExpr::orderHandle(ASTBool * const t_pBool) const
{
    if (dynamic_cast<ASTBoolExpr*>(t_pBool))
    {  
        return "(" + t_pBool->process() + ")";
    }
    return t_pBool->process();
}

std::string ASTBoolExpr::process()
{
    std::string rStr = ((isInversed()) ? "NOT(" : "") + orderHandle(pLeft);
    switch(m_op)
    {
    case LTHN:
        rStr += "<";
        break; 
    case LTHNEQ:
        rStr += "<=";
        break;
    case GTHN:
        rStr += ">";
        break;
    case GTHNEQ:
        rStr += ">=";
        break;
    case EQUAL:
        rStr += "==";
        break;
    case NEQUAL:
        rStr += "!=";
        break;
    case AND:
    case NAND:
        rStr += "AND";
        break;
    case OR:
    case NOR:
        rStr += "OR";
        break;
    }

    rStr += orderHandle(pRight) + ((isInversed()) ? ")" : "");
    if (rStr.size() > MAX_LINE_LENGTH)
    {
        std::string str = "Boolean expression is too long.  Consider using a higher optimization level.";
        throwError(str);
    }
    return rStr;
}

bool ASTBoolExpr::demorganFlip() const
{
    return pLeft->isInversed() || pRight->isInversed();
}

void ASTBoolExpr::inverse()
{
    switch(m_op)
    {
    case LTHN:
        m_op = GTHNEQ;
        break;
    case LTHNEQ:
        m_op = GTHN;
        break;
    case GTHN:
        m_op = LTHNEQ;
        break;
    case GTHNEQ:
        m_op = LTHN;
        break;
    case EQUAL:
        m_op = NEQUAL;
        break;
    case NEQUAL:
        m_op = EQUAL;
        break;
    case AND:
        if (demorganFlip())
        {
            pLeft->inverse();
            pRight->inverse();
            m_op = OR;
        }
        else
        {
            m_op = NAND;
        }
        break;
    case OR:
        if (demorganFlip())
        {
            pLeft->inverse();
            pRight->inverse();
            m_op = AND;
        }
        else
        {
            m_op = NOR;
        }
        break;
    case NAND:
        m_op = AND;
        break;
    case NOR:
        m_op = OR;
        break;
    }
}

bool ASTBoolExpr::isInversed() const
{
    switch(m_op)
    {
    case NAND:
    case NOR:
        return true;
    default:
        return false;
    }
}