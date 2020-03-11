#include "TypeService.h"
#include "GeneralTools.h"
#include <map>
#include <vector>

TypeService::TypeInfo::TypeInfo(const std::string& t_name, const TID t_id,
    const std::string * const t_aMembers, const TID * const t_aTypes, 
    const unsigned int t_numTypes) : name(t_name), id(t_id),
    aMembers(t_aMembers), aTypes(t_aTypes), numTypes(t_numTypes)
{}

TypeService::TypeInfo::~TypeInfo()
{
    delete[] aMembers;
    delete[] aTypes;
}

namespace TypeService
{
    TID nextID = 0;

    std::map<std::string, TID> keyMap;
    std::vector<TypeService::TypeInfo> valueMap;
}

const TypeService::TypeInfo TypeService::getInfo(const std::string& t_rStr)
{
    return getInfo(keyMap[t_rStr]);
}

const TypeService::TypeInfo TypeService::getInfo(const TID t_id)
{
    return valueMap[t_id];
}

const TypeService::TypeInfo TypeService::addType(const std::string& t_rStr,
    const TID * const t_aTypes, const std::string * const t_aMembers,
    const unsigned int t_typeCount)
{
    const TID id = nextID++;
    keyMap[t_rStr] = id;
    valueMap.emplace_back(t_rStr, id, t_aMembers, t_aTypes, t_typeCount);
    return valueMap[id];
}
void TypeService::initialize()
{
    valueMap.emplace_back(std::string("void"),  _void,      nullptr, nullptr, 0);
    valueMap.emplace_back(std::string("error"), error,      nullptr, nullptr, 0);
    valueMap.emplace_back(std::string("str"),   string,     nullptr, nullptr, 0);
    valueMap.emplace_back(std::string("num"),   number,     nullptr, nullptr, 0);
    valueMap.emplace_back(std::string("bool"),  boolean,    nullptr, nullptr, 0);
}