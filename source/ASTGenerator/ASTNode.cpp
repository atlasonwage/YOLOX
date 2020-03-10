#include "ASTNode.h"
#include <iostream>

bool ASTNode::errored() const
{
    return m_errored;
}

void ASTNode::throwError(const std::string& t_rStr)
{
    m_errored = true;
    std::cout << "[" << std::to_string(LINE_NUM) << "]: " << t_rStr << "\n";
}