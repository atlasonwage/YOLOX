#include "ASTVar.h"

ASTVar::ASTVar(unsigned int t_referenceLine, TID t_type, const VarCategory t_category, 
    VID t_id, bool t_isConst) : ASTOpParam(t_referenceLine), CATEGORY(t_category), 
    ID(t_id), IS_CONST(t_isConst), m_type(t_type)
{}

std::string ASTVar::process()
{
    return VarReferencer::getVarInfo(CATEGORY, ID).compiledName;
}

bool ASTVar::operator==(const ASTVar& t_rBase)
{
    return CATEGORY == t_rBase.CATEGORY && ID == t_rBase.ID;
}

TID ASTVar::getType() const
{
    return m_type;
}