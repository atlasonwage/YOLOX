#pragma once
#include <string>
#include "TypeService.h"

typedef unsigned int VID;

enum class VarType {LOCAL = 0, FIELD, SUBROUTINE};

namespace VarReferencer
{
    struct VarInfo
    {
        const VarType vType;
        const VID id;                       //IDs are unique within the same var. types
        const std::string translationName;
        std::string compiledName;
    };

    const VarInfo registerVar(const std::string& t_rStr);
    const VarInfo registerField(const std::string& t_rStr);

    const VarInfo getVarInfo(const VarType t_type, const VID t_id);
    const VarInfo getVarInfo(const std::string& t_name);

    //Auto-generated variable name helper functions
    //Allocates 2 + t_paramCount variables
    const VID registerSubroutineVars(unsigned int t_paramCount);
}