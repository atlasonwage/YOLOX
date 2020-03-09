#include "TypeService.h"
#include "../BiTree/BiTree.h"
#include "GeneralTools.h"

TID nextID = TypeService::boolean + 1;

BiTree<std::string, TID> typeTree;

std::string TypeService::getNameFromTID(const TID t_id)
{
    std::string rStr = typeTree.findKey(t_id);
    if (rStr == "") { rStr = "error"; }   
    return rStr;
}

TID TypeService::getTIDFromName(const std::string& t_rStr)
{
    return typeTree.find(t_rStr);
}

TID TypeService::addType(const std::string& t_rStr)
{
    typeTree.insert(t_rStr, nextID++);
}

void TypeService::initialize()
{
    typeTree.insert(std::string("error"), static_cast<TID>(0));
    typeTree.insert(std::string("string"), static_cast<TID>(1));
    typeTree.insert(std::string("number"), static_cast<TID>(2));
    typeTree.insert(std::string("boolean"), static_cast<TID>(3));
}