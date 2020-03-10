#include "TypeService.h"
#include "GeneralTools.h"
#include <map>

TID nextID = 0;

std::map<std::string, TID> keyMap;
std::map<TID, TypeService::TypeInfo> valueMap;

const TypeService::TypeInfo TypeService::getInfo(const std::string& t_rStr)
{
    return getInfo(keyMap[t_rStr]);
}

const TypeService::TypeInfo TypeService::getInfo(const TID t_id)
{
    return valueMap[t_id];
}

const TypeService::TypeInfo TypeService::addType(const std::string& t_rStr)
{
    const TID id = nextID++;
    keyMap[t_rStr] = id;
    valueMap[id] = TypeInfo{t_rStr, id};
}

void TypeService::initialize()
{
    addType(std::string("void"));
    addType(std::string("error"));
    addType(std::string("str"));
    addType(std::string("num"));
    addType(std::string("bool"));
}