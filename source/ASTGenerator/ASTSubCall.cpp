#include "ASTSubCall.h"

ASTSubCall::ASTSubCall (unsigned int t_referenceLine, SID t_id, 
    const std::vector<ASTOpParam*> t_params) : ASTNode(t_referenceLine), m_id(t_id),
    m_params(t_params)
{
    //Do type checking on provided parameters.
    SubroutineManager::SubroutineStruct str = SubroutineManager::getSubroutine(t_id);
    bool error = false;
    if (str.parameters.size() == t_params.size())
    {
        for(unsigned int i = 0; i < t_params.size(); ++i)
        {
            if (t_params[i]->getType() != str.parameters[i].getType())
            {
                error = true;
                break;
            }
        }
    }
    else
    {
        error = true;
    }

    if (error)
    {
        std::string str = "Could not find parameter list (";
        if (t_params.size() == 0)
        {
            str += "void).";
        } else {
            str += TypeService::getInfo(t_params[0]->getType()).name;
            for (unsigned int i = 1; i < t_params.size(); ++i)
            {
                str += ", " + TypeService::getInfo(t_params[i]->getType()).name;
            }
            str += ").";
        }
        throwError(str);
    }
}

ASTSubCall::~ASTSubCall ()
{
    for (unsigned int i = 0; i < m_params.size(); ++i)
    {
        delete &(m_params[i]);
    }
}

std::string ASTSubCall::process()
{
    std::string rStr;
    SubroutineManager::SubroutineStruct str = SubroutineManager::getSubroutine(m_id);
    std::string line;
    for(unsigned int i = 0; i < m_params.size(); ++i)
    {
        std::string text = str.parameters[i].process() + "=" + m_params[i]->process();
        if (text.size() > MAX_LINE_LENGTH)
        {
            rStr = "Parameter expression is too large.  Consider using a variable or using a higher optimization level.";
            throwError(rStr);
        }

        if (line.size() == 0)
        {
            line = text;
        } else if (line.size() + text.size() + 1 <= MAX_LINE_LENGTH) {
            line += " " + text;
        } else {
            rStr += "\n" + line;
            line = text;
        }
    }
    std::string text = str.entryPoint.process() + "=$LINE+";
    if (line.size() + text.size() + RESERVED_GOTO_LENGTH - 6 <= MAX_LINE_LENGTH)
    {
        line += " " + text;

        //Check to place goto in same line
        if (line.size() + 2*RESERVED_GOTO_LENGTH <= MAX_LINE_LENGTH)
        {
            line += std::to_string(1) + " goto $SUBR" + std::to_string(str.id);
        }
        else
        {
            line += std::to_string(2) + "\ngoto $SUBR" + std::to_string(str.id);
        }
    } else {
        rStr += "\n" + line;
        line = text;
        if (line.size() + 2*RESERVED_GOTO_LENGTH <= MAX_LINE_LENGTH)
        {
            line += std::to_string(1) + " goto $SUBR" + std::to_string(str.id);
        }
        else
        {
            line += std::to_string(2) + "\ngoto $SUBR" + std::to_string(str.id);
        }
    }

    return rStr + line;
}