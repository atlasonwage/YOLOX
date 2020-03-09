#include "ASTBlock.h"

ASTBlock::ASTBlock(unsigned int t_referenceLine) : ASTNode(t_referenceLine)
{}

ASTBlock::~ASTBlock()
{
    //Cleans up children
    for(unsigned int i = 0; i < children.size(); ++i)
    {
        delete *(children[i]);
    }
}

virtual std::string ASTBlock::process() const
{
    std::string rStr;
    std::string line;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        if (line.size() == 0)
        {
            line = children[i];
        }
        else if (line.size() + children[i].size() + 1 > MAX_LINE_LENGTH)
        {
            rStr += "\n" + line;
            line = children[i];
        }
        else
        {
            line += " " + children[i];
        }
    }

    return rStr + line;
}

void ASTBlock::addChild(ASTNode * const t_pNode)
{
    children.push_back(t_pNode);
}