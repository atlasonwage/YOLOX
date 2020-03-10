#pragma once
#include "ASTBool.h"
#include "ASTVar.h"

class ASTBoolVar : public ASTBool, public ASTVar
{
public:
    ASTBoolVar(unsigned int t_referenceLine, const VarCategory t_category, 
        VID t_id, bool is_const = false);

    virtual std::string process() override;
    virtual void inverse();
    virtual bool isInversed() const;

    bool operator==(const ASTBoolVar& t_rBase);
private:
    bool m_isInversed = false;
};