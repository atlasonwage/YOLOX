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
    typeTree.insert(std::string("void"), _void);
    typeTree.insert(std::string("error"), error);
    typeTree.insert(std::string("str"), string);
    typeTree.insert(std::string("num"), number);
    typeTree.insert(std::string("bool"), boolean);
}