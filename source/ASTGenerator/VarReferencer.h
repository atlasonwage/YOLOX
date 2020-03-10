#pragma once
#include <string>
#include "TypeService.h"

typedef unsigned int VID;

namespace VarReferencer
{
    //Returns the string name of the field from id
    std::string getFieldFromID(VID t_id);
    std::string getVarFromID(VID t_id);

    //Registers a general-purpose variable.
    const VID registerVar(const std::string& t_rStr);
    //Registers a field variable.
    const VID registerField(const std::string& t_rStr);

    //Auto-generated variable name helper functions
    //Allocates 2 + t_paramCount variables
    const VID registerSubroutineVars(unsigned int t_paramCount);
}