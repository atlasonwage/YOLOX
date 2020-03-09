#pragma once
#include "ASTNode.h"

//Represents a varaible or field.
class ASTVar : public ASTNode
{
public:
    const bool IS_FIELD;
    const unsigned int ID;

    ASTVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField);
    virtual std::string process() const override;
};