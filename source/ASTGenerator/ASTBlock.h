#pragma once
#include "ASTNode.h"
#include <vector>

//Reprsents a group of Nodes.
//Blocks have line priority, as the contents may require it.
//For greater efficiency, use block merging.
class ASTBlock : public ASTNode
{
public:
    ASTBlock(unsigned int t_referenceLine);
    ~ASTBlock();
    
    //Processes the children and this node.
    std::string process() const override;

    //A child is added to the node.
    void addChild(ASTNode * const t_pChild);

    //Takes all the target's children and appends them to the current children.
    //The target's children are then cleared.
    void merge(ASTBlock * const t_pTarget);
protected:
    std::vector<ASTNode*> children;
};