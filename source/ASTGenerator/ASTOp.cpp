#include "ASTOp.h"
#include "ASTVar.h"

ASTOp::ASTOp(unsigned int t_referenceLine, const Op t_op,
    ASTOpParam * const t_pLeft, ASTOpParam * const t_pRight = nullptr) :
    ASTOpParam(t_referenceLine), m_op(t_op), m_pLeft(t_pLeft), m_pRight(t_pRight)
{
    //Check for assignment optimizations
    if (m_op == ASSIGN)
    {
        //Is right child an operation?
        ASTOp * const pAssignee = dynamic_cast<ASTOp*>(m_pRight);
        if (m_pRight)
        {
            bool upgrade = false;
            //Is the assignment target the same?
            switch(pAssignee->m_op)
            {
            case ADD:
            case MUL:
                ASTVar * pVar = dynamic_cast<ASTVar*>(pAssignee->m_pRight);
                if (pVar && *pVar == *reinterpret_cast<ASTVar*>(m_pLeft))
                {
                    upgrade = true;
                    pAssignee->m_pRight = nullptr;
                }
            case SUB:
            case DIV:
            case MOD:
                ASTVar * pVar = dynamic_cast<ASTVar*>(pAssignee->m_pLeft);
                if (pVar && *pVar == *reinterpret_cast<ASTVar*>(m_pLeft))
                {
                    upgrade = true;
                    pAssignee->m_pLeft = nullptr;
                }

                if (upgrade)
                {
                    //Optimize away the node.
                    switch(pAssignee->m_op)
                    {
                    case ADD:
                        m_op = ADD_ASSIGN;
                        break;
                    case SUB:
                        m_op = SUB_ASSIGN;
                        break;
                    case MUL:
                        m_op = MUL_ASSIGN;
                        break;
                    case DIV:
                        m_op = DIV_ASSIGN;
                        break;
                    case MOD:
                        m_op = MOD_ASSIGN;
                        break;
                    }
                    delete pAssignee;
                }
                break;
            }
        }
    }
    //Check for const violations
    switch(m_op)
    {
    case ASSIGN:
    case PRE_INC:
    case POST_INC:
    case PRE_DEC:
    case POST_DEC:
    case ADD_ASSIGN:
    case SUB_ASSIGN:
    case MUL_ASSIGN:
    case DIV_ASSIGN:
    case MOD_ASSIGN:
    case EXP_ASSIGN:
        ASTVar * const pVar = dynamic_cast<ASTVar*>(m_pLeft);
        if (pVar && pVar->IS_CONST)
        {
            std::string str = "Assignment of constant type";
            throwError(str, t_referenceLine);
        }
    }

    //Check for type violations
    if (m_pRight && m_pLeft->getType() != m_pRight->getType())
    {
        std::string str = "Type mismatch: " + TypeService::getInfo(m_pLeft->getType()).name
            + ", " + TypeService::getInfo(m_pRight->getType()).name;
        throwError(str, t_referenceLine);
    }

    //Maybe check to remove unneeded assignments
}

ASTOp::~ASTOp()
{
    delete m_pLeft;
    delete m_pRight;
}

std::string ASTOp::process() const
{
    std::string rStr;

    switch(m_op)
    {
    case PRE_INC:
    case PRE_DEC:
    case ABS:
    case SQRT:
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
        rStr = opString(m_op) + m_pLeft->process();
        break;
    case POST_INC:
    case POST_DEC:
    case FACT:
        rStr = m_pLeft->process() + opString(m_op);
        break;
    default:
        if (m_op == EXP_ASSIGN)
        {
            rStr = m_pLeft->process() + "=" + m_pLeft->process() + "^" + m_pRight->process();
        }
        else
        {
            rStr = m_pLeft->process() + opString (m_op) + m_pRight->process();
        }
        break;
    }
    return rStr;
}

/* Operator overriding is not permitted currently.  Thus, all operations must be on
 * numbers, strings, or bools.
 * Only the left operator's type is passed, as all types will be explicitly casted.
 */
TID ASTOp::getType() const
{
    return m_pLeft->getType();
}

std::string ASTOp::opString(const Op t_op)
{
    std::string rStr;

    switch(t_op)
    {
    case ADD:
        rStr = "+";
        break;
    case SUB:
        rStr = "-";
        break;
    case MUL:
        rStr = "*";
        break;
    case DIV:
        rStr = "/";
        break;
    case MOD:
        rStr = "%";
        break;
    case EXP:
    case EXP_ASSIGN:
        rStr = "^";
        break;
    case PRE_INC:
    case POST_INC:
        rStr = "++";
        break;
    case PRE_DEC:
    case POST_DEC:
        rStr = "--";
        break;
    case ASSIGN:
    case CASSIGN:
        rStr = "=";
        break;
    case ADD_ASSIGN:
        rStr = "+=";
        break;
    case SUB_ASSIGN:
        rStr = "-=";
        break;
    case MUL_ASSIGN:
        rStr = "*=";
        break;
    case DIV_ASSIGN:
        rStr = "/=";
        break;
    case MOD_ASSIGN:
        rStr = "%=";
        break;
    case ABS:
        rStr = "ABS ";
        break;
    case FACT:
        rStr = "!";
        break;
    case SQRT:
        rStr = "SQRT ";
        break;
    case SIN:
        rStr = "SIN ";
        break;
    case COS:
        rStr = "COS ";
        break;
    case TAN:
        rStr = "TAN ";
        break;
    case ASIN:
        rStr = "ASIN ";
        break;
    case ACOS:
        rStr = "ACOS ";
        break;
    case ATAN:
        rStr = "ATAN ";
        break;
    }

    return rStr;
}