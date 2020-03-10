#pragma once
#include <string>
#include "TypeService.h"

typedef unsigned int VID;

//Error represents an internal error
enum class VarCategory {LOCAL = 0, FIELD, SUBROUTINE, ERROR};

namespace VarReferencer
{
    struct VarInfo
    {
        const VarCategory vType;
        const VID id;                       //IDs are unique within the same var. types
        const std::string translationName;
        std::string compiledName;

        VarInfo(const VarCategory t_type, const VID t_id, 
            const std::string& t_translationName, const std::string& t_compiledName);
        VarInfo();
        ~VarInfo();
    };

    const VarInfo registerVar(const std::string& t_rStr);
    const VarInfo registerField(const std::string& t_rStr);

    const VarInfo getVarInfo(const VarCategory t_type, const VID t_id);
    const VarInfo getVarInfo(const std::string& t_name);

    //Auto-generated variable name helper functions
    //Allocates 2 + t_paramCount variables
    const VID registerSubroutineVars(unsigned int t_paramCount);
}