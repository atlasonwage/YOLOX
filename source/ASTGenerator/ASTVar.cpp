#include "ASTVar.h"
#include "VarReferencer.h"

ASTVar::ASTVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField) : 
    ASTNode(t_referenceLine), IS_FIELD(t_isFiled), ID(t_id)
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