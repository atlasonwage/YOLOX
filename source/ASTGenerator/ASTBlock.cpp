#include "ASTBlock.h"

ASTBlock::ASTBlock(unsigned int t_referenceLine) : ASTNode(t_referenceLine, true)
{}

ASTBlock::~ASTBlock()
{
    //Cleans up children
    for(unsigned int i = 0; i < children.size(); ++i)
    {
        delete children[i];
    }
}

std::string ASTBlock::process()
{
    std::string rStr;
    std::string line;
    bool firstLine = true;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        std::string text = children[i]->process();
        if (line.size() == 0)
        {
            line = text;
        }
        else if (((line.size() + text.size() + 1) > MAX_LINE_LENGTH)
            || ((i > 0) ? (children[i-1]->m_linePriority) : false))
        {
            rStr += ((firstLine) ? "" : "\n") + line;
            firstLine = false;
            line = text;
        }
        else
        {
            line += " " + text;
        }
    }

    return rStr + ((firstLine) ? "" : "\n") + line;
}

void ASTBlock::addChild(ASTNode * const t_pNode)
{
    //Auto-merges blocks.
    ASTBlock * const pBlock = dynamic_cast<ASTBlock*>(t_pNode);
    if (pBlock)
    {
        merge(pBlock);
        delete pBlock;
    } else {
        children.push_back(t_pNode);
    }
}

void ASTBlock::merge(ASTBlock * const t_pBase)
{
    for (unsigned int i = 0; i < t_pBase->children.size(); ++i)
    {
        children.push_back(t_pBase->children[i]);
    }
    t_pBase->children.clear();
}