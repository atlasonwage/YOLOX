#pragma once
#include "ASTNode.h"

//Reprsents a group of Nodes.
class ASTBlock
{
public:
    ASTBlock(unsigned int t_referenceLine);
    ~ASTBlock();
    
    //Processes the children and this node.
    virtual std::string process() const override;

    //A child is added to the node.
    void addChild(ASTNode * const t_pChild);
protected:
    std::vector<ASTNode*> children;
};