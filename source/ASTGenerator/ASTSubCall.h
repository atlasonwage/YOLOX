#pragma once
#include "ASTNode.h"
#include "ASTOpParam.h"
#include "SubroutineManager.h"

//Represents a call to a subroutine
//Subroutine calls have line priority
class ASTSubCall : public ASTNode
{
public:
    ASTSubCall(unsigned int t_referenceLine, SID t_id, const std::vector<ASTOpParam*> t_params);
    ~ASTSubCall();
    
    virtual std::string process() override;
private:
    const SID m_id;
    std::vector<ASTOpParam*> m_params;
};