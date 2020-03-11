#pragma once
#include <ASTNode.h>

class ASTDummy : public ASTNode
{
public:
    ASTDummy(unsigned int t_lineNum, const std::string& t_rStr, bool t_priority = false) :
        ASTNode(t_lineNum, t_priority), m_text(t_rStr)
    {}
    ~ASTDummy(){};

    std::string process() override
    {
        return m_text;
    }

private:
    std::string m_text;
};