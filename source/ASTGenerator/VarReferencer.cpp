#include "VarReferencer.h"
#include "GeneralTools.h"
#include <map>

//Automatically starts the optimization levels at none.
IdentifierOptimizationLevel varOptimizationLevel = IdentifierOptimizationLevel::NONE;
IdentifierOptimizationLevel fieldOptimizationLevel = IdentifierOptimizationLevel::NONE;

namespace VarReferencer
{
    //One id for each type of VariableType
    VID nextId[] = {0, 0, 0};
}

using namespace VarReferencer;

struct SearchPair
{
    VarCategory vType;
    TID     id;

    friend bool operator< (const SearchPair& t_left, const SearchPair& t_right)
    {
        return (t_left.vType == t_right.vType) ? (t_left.id < t_right.id)
            : (t_left.vType < t_right.vType);
    }

    SearchPair(const VarCategory t_type, const TID t_id) :
        vType(t_type), id(t_id) {}
    SearchPair() : SearchPair(VarCategory::ERROR, 0) {}
    ~SearchPair() {}
};

VarReferencer::VarInfo::VarInfo(const VarCategory t_type, const VID t_id, 
    const std::string& t_translationName, const std::string& t_compiledName) :
    vType(t_type), id(t_id), translationName(t_translationName),
    compiledName(t_compiledName)
{}
VarReferencer::VarInfo::VarInfo() : VarInfo(VarCategory::ERROR, 0,
    std::string(), std::string())
{}

VarReferencer::VarInfo::~VarInfo()
{}


std::map<std::string, SearchPair>               translateMap;
std::map<SearchPair, VarReferencer::VarInfo>    infoMap;

const unsigned int MIN_LOW_STR_LENGTH = 3;

char formatedInt(unsigned int t_int)
{
    t_int %= 36;
    if (t_int < 10)
    {
        //Numerical characters.
        return static_cast<char>(0x30 + t_int);
    } else {
        //lowercase letters
        return static_cast<char>(0x61 + t_int - 10);
    }
}

std::string idToName(VID t_id)
{
    std::string name;
    while (t_id >= 36)
    {
        name[name.size()] = formatedInt(t_id);
        t_id /= 36;
    }
    name[name.size()] = formatedInt(t_id);
    return name;
}

std::string optimizeName(const std::string& t_rStr, 
    const VarCategory t_type)
{
    const IdentifierOptimizationLevel optLevel =
        (t_type == VarCategory::LOCAL) ? varOptimizationLevel :
        (
            (t_type == VarCategory::FIELD) ? fieldOptimizationLevel :
                IdentifierOptimizationLevel::HIGH
        );
    switch(optLevel)
    {
    case IdentifierOptimizationLevel::NONE:
        return t_rStr;

    case IdentifierOptimizationLevel::LOW:
        //TODO
        return t_rStr;

    case IdentifierOptimizationLevel::HIGH:
        std::string name = ((t_type == VarCategory::FIELD) ? ":F" : "V") + 
            idToName(translateMap[t_rStr].id);
        return name;
    }
}

const VarReferencer::VarInfo reg(
    const std::string& t_rStr, const VarCategory t_type,
    const IdentifierOptimizationLevel t_optLevel)
{
    const SearchPair pair = {t_type, nextId[static_cast<int>(t_type)]++};
    translateMap[t_rStr] = pair;
    infoMap.emplace(std::make_pair(pair, 
        VarReferencer::VarInfo
            {t_type, pair.id, t_rStr, 
            optimizeName(t_rStr, t_type)
            }
        ));
    return infoMap[pair];
}

const VarReferencer::VarInfo VarReferencer::registerVar
    (const std::string& t_rStr)
{
    return reg(t_rStr, VarCategory::LOCAL, varOptimizationLevel);
}

const VarReferencer::VarInfo VarReferencer::registerField
    (const std::string& t_rStr)
{
    return reg(t_rStr, VarCategory::FIELD, fieldOptimizationLevel);
}

const VarReferencer::VarInfo VarReferencer::getVarInfo(const VarCategory t_type, const VID t_id)
{
    return infoMap[SearchPair{t_type, t_id}];
}

const VarReferencer::VarInfo getVarInfo(const std::string& t_name)
{
    return infoMap[translateMap[t_name]];
}


const VID VarReferencer::registerSubroutineVars(unsigned int t_paramCount)
{
    //Get IDs in use.
    const VID id = nextId[static_cast<int>(VarCategory::SUBROUTINE)];
    nextId[static_cast<int>(VarCategory::SUBROUTINE)] += 2 + t_paramCount;
    //Note that no translation string is needed.
    for (unsigned int i = 0; i < 2 + t_paramCount; ++i)
    {
        std::string name = "S" + idToName(id + i);
        infoMap.emplace(std::make_pair(
            SearchPair{VarCategory::SUBROUTINE, id + i},
            VarInfo{VarCategory::SUBROUTINE, id + i, std::string(), name}            
        ));
    }

    return id;
}