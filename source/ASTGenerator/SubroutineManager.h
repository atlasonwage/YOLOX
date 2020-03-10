#pragma once
#include <string>
#include <vector>
#include "ASTBoolVar.h"

typedef unsigned int SID;

namespace SubroutineManager
{
    struct SubroutineStruct
    {
        unsigned int line;              //Zero until the code compiles, then is filled in.  Used for function call replacements.
        SID id;                         //Subroutines with different parameter lists will have different SIDs
        std::string name;
        ASTVar entryPoint;              //guarenteed to exist and to be of type "number"
        union RET_VAR                     //may exist; to check if it is boolean, check the type of nonBinary
        {
            ASTVar nonBinary;
            ASTBoolVar binary;

            RET_VAR(const ASTVar& t_rBase);
            RET_VAR(const ASTBoolVar& t_rBase);
        } returnVar;
        std::vector<ASTVar> parameters; //may not have any parameters
        ASTNode * const pBody;

        bool operator==(const SubroutineStruct& t_rBase);
        SubroutineStruct(const SubroutineStruct& t_rBase);

        SubroutineStruct(unsigned int t_line, SID t_id, const std::string& t_name, 
            const ASTVar& t_entryPoint, const ASTVar& t_returnVar, 
            const std::vector<ASTVar>& t_parameters, ASTNode * const t_pBody);

        SubroutineStruct(unsigned int t_line, SID t_id, const std::string& t_name, 
            const ASTVar& t_entryPoint, const ASTBoolVar& t_returnVar, 
            const std::vector<ASTVar>& t_parameters, ASTNode * const t_pBody);
    };

    //Register a subroutine to the service
    const SubroutineStruct registerSubroutine(const std::string& t_name, unsigned int t_referenceLine, 
        const TID t_returnType, const std::vector<TID>& t_params, ASTNode * const t_pBodyRoot);
    
    //Get a subroutine from the service by name.
    const SubroutineStruct getSubroutine(const std::string& t_name, const std::vector<TID>& t_params);
    const SubroutineStruct getSubroutine(const SID t_id);

    //Returns the compiled subroutine call code
    const std::string processSubroutine(const std::string& t_name, const std::vector<TID>& t_params);
    const std::string processSubroutine(const SID t_id);
}