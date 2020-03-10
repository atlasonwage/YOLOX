#pragma once
#include "ASTBool.h"
#include "ASTBlock.h"

//General-purpose loop structure
//loops have line priority
class ASTLoop : public ASTNode
{
public:
    enum ConditionalCheck {PRE, POST};

    ASTLoop(unsigned int t_referenceLine, ASTBool * const t_pCondtion, 
        ASTBlock * const t_pBody, const ConditionalCheck t_check = PRE, 
        ASTBlock * const t_pInitializerBlock = nullptr,
        ASTBlock * const t_pPostUpdateBlock = nullptr);
    ~ASTLoop();

    std::string process() const override;
private:
    const ConditionalCheck m_check;
    ASTBool * const m_pCondition;
    ASTBlock * const m_pBody;
    ASTBlock * const m_pInitialize;
};