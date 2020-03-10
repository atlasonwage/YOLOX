#include "ASTVar.h"

ASTVar::ASTVar(unsigned int t_referenceLine, TID t_type, VID t_id, bool t_isField, 
    bool t_isConst) : ASTOpParam(t_referenceLine), m_type(t_type),
    IS_FIELD(t_isField), ID(t_id), IS_CONST(t_isConst)
{}

std::string ASTVar::process() const
{
    if (IS_FIELD)
    {
        return VarReferencer::getFieldFromID(ID);
    }
    else
    {
        return VarReferencer::getVarFromID(ID);
    }
}

bool ASTVar::operator==(const ASTVar& t_rBase)
{
    return IS_FIELD == t_rBase.IS_FIELD && ID == t_rBase.ID;
}

TID ASTVar::getType() const
{
    return m_type;
}