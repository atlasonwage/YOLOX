#include "ASTConditional.h"

ASTConditional::ASTConditional(unsigned int t_referenceLine, ASTBool * const t_pConditional, 
    ASTNode * const t_pTrue, ASTNode * const t_pFalse) : ASTNode(t_referenceLine, true),
    m_pConditional(t_pConditional), m_pTrue (t_pTrue), m_pFalse(t_pFalse)
{}

ASTConditional::~ASTConditional()
{
    delete m_pConditional;
    delete m_pTrue;
    delete m_pFalse;
}

std::string ASTConditional::process()
{
    std::string rStr;
    std::string rCond = m_pConditional->process();
    std::string rTrue = m_pTrue->process();
    if (m_pFalse)
    {
        std::string rFalse = m_pFalse->process();
        
        if (rTrue.size() + rFalse.size() + rCond.size() + ELSE_CONDITIONAL_LENGTH <= MAX_LINE_LENGTH)
        {
            //All text fits
            rStr = "if " + rCond + " then " + rTrue + " else " + rFalse + " end";
        }
        else if (rTrue.size() + rCond.size() + GOTO_SKIP_LENGTH <= MAX_LINE_LENGTH)
        {
            //False text needs its own line(s)
            rStr = "if " + rCond + " then " + rTrue + " goto $LINE+" + 
                std::to_string(1 + linesInString(rFalse)) + " end\n" + rFalse;
        }
        else
        {
            m_pConditional->inverse();
            rCond = m_pConditional->process();
            m_pConditional->inverse();

            if (rFalse.size() + rCond.size() + GOTO_SKIP_LENGTH <= MAX_LINE_LENGTH)
            {
                //True text needs its own line(s)
                rStr = "if " + rCond + " then " + rFalse + " goto $LINE+" +
                    std::to_string(1 + linesInString(rTrue)) + " end\n" + rTrue;
            }
            else if (rCond.size() + GOTO_SKIP_LENGTH <= MAX_LINE_LENGTH)
            {
                //Both conditions need their own line(s)
                rStr = "if " + rCond + " then goto $LINE+" + std::to_string(2 + linesInString(rTrue))
                    + " end\n" + rTrue + "\ngoto $LINE+" + std::to_string(1 + linesInString(rFalse))
                    + "\n" + rFalse;
            }
            else
            {
                rStr = "Condition text was too large.  Consider renaming variables or \
                        using a higher optimization level.";
                throwError(rStr);
            }
        }
    }
    else
    {
        if (CONDITIONAL_LENGTH + rTrue.size() + rCond.size() <= MAX_LINE_LENGTH)
        {
            //Condition fits on line
            rStr = "if " + rCond + " then " + rTrue + " end";
        }
        else
        {
            //Condition needs its own line(s)
            m_pConditional->inverse();
            rCond = m_pConditional->process();
            m_pConditional->inverse();
            if (GOTO_SKIP_LENGTH + rCond.size() <= MAX_LINE_LENGTH)
            {
                rStr = "if " + rCond + " then goto $LINE+" + std::to_string(linesInString(rTrue) + 1) 
                + " end\n" + rTrue;
            }
            else
            {
                rStr = "Condition text was too large.  Consider renaming variables or \
                        using a higher optimization level.";
                throwError(rStr);
            }
        }
    }
    return rStr;
}