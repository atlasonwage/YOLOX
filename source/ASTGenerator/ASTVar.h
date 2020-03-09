#pragma once
#include "ASTOpParam.h"

//Represents a varaible or field.
class ASTVar : public ASTOpParam
{
public:
    const bool IS_FIELD;
    const unsigned int ID;

    ASTVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField);
    virtual std::string process() const override;

    bool operator==(const ASTVar& t_rBase);
};