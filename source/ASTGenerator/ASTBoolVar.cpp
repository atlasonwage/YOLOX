#include "ASTBoolVar.h"

ASTBoolVar::ASTBoolVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField,
    bool t_isConst) : ASTVar(t_referenceLine, t_id, t_isField, t_isConst),
    ASTBool(t_referenceLine)
{}

std::string ASTBoolVar::process() const
{
    std::string rStr;
    if (m_isInversed)
    {
        rStr = "NOT(";
    }
    rStr += ASTVar::process();
    if (m_isInversed)
    {
        rStr += ")";
    }
    return rStr;
}

void ASTBoolVar::inverse()
{
    m_isInversed = !m_isInversed;
}

bool ASTBoolVar::isInversed() const
{
    return m_isInversed;
}

bool ASTBoolVar::operator==(const ASTBoolVar& t_rBase)
{
    return ASTVar::operator==(t_rBase) && m_isInversed == t_rBase.m_isInversed;
}