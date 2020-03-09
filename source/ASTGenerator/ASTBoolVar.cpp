#include "ASTBoolVar.h"

ASTBoolVar::ASTBoolVar(unsigned int t_referenceLine, unsigned int t_id, bool t_isField) :
    ASTVar(t_referenceLine, t_id, t_isField)
{}

virtual std::string ASTBoolVar::process() const
{
    string rStr;
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

virtual void ASTBoolVar::inverse()
{
    m_isInversed = !m_isInversed;
}

virtual bool ASTBoolVar::m_isInversed() const
{
    return m_isInversed;
}

bool ASTBoolVar::operator==(const ASTBoolVar& t_rBase)
{
    return ASTVar::operator==(t_rBase) && m_isInversed == t_rBase.m_isInversed;
}