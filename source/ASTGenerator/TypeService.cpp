#include "TypeService.h"
#include "GeneralTools.h"
#include <map>
#include <vector>

TID nextID = 0;

std::map<std::string, TID> keyMap;
std::vector<TID, TypeService::TypeInfo> valueMap;

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
}
void TypeService::initialize()
{
    valueMap[_void]     = TypeInfo{std::string("void"),     _void,      nullptr, &_void,     1};
    valueMap[error]     = TypeInfo{std::string("error"),    error,      nullptr, &error,     1};
    valueMap[string]    = TypeInfo{std::string("str"),      string,     nullptr, &string,    1};
    valueMap[number]    = TypeInfo{std::string("num"),      number,     nullptr, &number,    1};
    valueMap[boolean]   = TypeInfo{std::string("bool"),     boolean,    nullptr, &boolean,   1};
}

void TypeService::cleanUp()
{
    keyMap.clear();
    auto begin = valueMap.begin();
    auto end = valueMap.end();
    //Skip the primitives
    for (unsigned int i = 0; i <= boolean; ++i, ++begin) {}
    //Remove dymanically-allocated types
    while (begin != end)
    {
        delete[] begin->second.pType;
        ++begin;
    }
}