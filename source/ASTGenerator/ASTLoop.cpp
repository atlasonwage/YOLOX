#include "ASTLoop.h"
#include "ASTConditional.h"

ASTLoop::ASTLoop(unsigned int t_referenceLine, ASTBool * const t_pCondtion, 
        ASTBlock * const t_pBody, const ConditionalCheck t_check, 
        ASTBlock * const t_pInitializerBlock,
        ASTBlock * const t_pPostUpdateBlock) : ASTNode(t_referenceLine, true),
        m_check(t_check), m_pCondition(t_pCondtion), m_pBody(t_pBody),
        m_pInitialize(t_pInitializerBlock)
{
    //the update block cannot be used with a post-check direction
    if (t_pPostUpdateBlock && t_check == PRE)
    {
        m_pBody->merge(t_pPostUpdateBlock);
        delete t_pPostUpdateBlock;
    }
}

ASTLoop::~ASTLoop()
{
    delete m_pInitialize;
    delete m_pBody;
    delete m_pCondition;
}

std::string ASTLoop::process()
{
    std::string rStr;
    std::string body = m_pBody->process();
    unsigned int bSize = linesInString(body);
    if (m_pInitialize)
    {
        rStr = m_pInitialize->process();
    }
    if (m_check == PRE)
    {
        m_pCondition->inverse();
        rStr += "\nif " + m_pCondition->process() + " then goto $LINE+" + std::to_string(2 + bSize) 
            + " end\n";
        m_pCondition->inverse();
    }
    rStr += body;
    if (m_check == PRE)
    {
        if (lastLineLength(rStr) + 6 + RESERVED_GOTO_LENGTH <= MAX_LINE_LENGTH)
        {
            rStr += " goto $LINE-" + std::to_string(2 + bSize);
        } else {
            rStr += "\ngoto $LINE-" + std::to_string(2 + bSize);
        }
    } else {
        rStr += "\nif " + m_pCondition->process() + " then goto $LINE-" + std::to_string(bSize)
            + " end";
    }
    return rStr;
}