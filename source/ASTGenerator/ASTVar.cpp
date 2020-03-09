#include "ASTVar.h"
#include "VarReferencer.h"

ASTVar::ASTVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField) : 
    ASTOpParam(t_referenceLine), IS_FIELD(t_isFiled), ID(t_id)
{}

virtual std::string ASTVar::process() const
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