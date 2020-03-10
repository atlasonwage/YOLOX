#pragma once
#include "ASTOpParam.h"
#include "VarReferencer.h"

//Represents a varaible or field.
class ASTVar : public ASTOpParam
{
public:
    const bool IS_FIELD;
    const VID ID;
    const bool IS_CONST;

    ASTVar(unsigned int t_referenceLine, TID t_type, VID t_id,
        bool t_isField, bool t_isConst = false);
    virtual std::string process() const override;

    bool operator==(const ASTVar& t_rBase);

    TID getType() const override;
private:
    const TID m_type;
};