#include "SubroutineManager.h"
#include "VarReferencer.h"
#include <map>

namespace SubroutineManager
{
    SID nextId = 0;

    std::map<std::string, SID> keyMap;
    std::map<SID, SubroutineManager::SubroutineStruct> structMap;
}

using namespace SubroutineManager;

std::string standardName (const std::string& t_name, const std::vector<TID>& t_params)
{
    std::string rStr = t_name;
    for (unsigned int i = 0; i < t_params.size(); ++i)
    {
        rStr += "." + std::to_string(t_params[i]);
    }
    return rStr;
}

//Value equality is ID based
bool SubroutineManager::SubroutineStruct::operator== (const SubroutineManager::SubroutineStruct& t_rBase)
{
    return id == t_rBase.id;
}

SubroutineManager::SubroutineStruct::RET_VAR::RET_VAR(const ASTVar& t_rBase) :
    nonBinary(t_rBase)
{}

SubroutineManager::SubroutineStruct::RET_VAR::RET_VAR(const ASTBoolVar& t_rBase) :
    binary(t_rBase)
{}

SubroutineManager::SubroutineStruct::RET_VAR::~RET_VAR() {}

SubroutineManager::SubroutineStruct::SubroutineStruct() :
    SubroutineStruct(0, 0, std::string(), ASTVar(0, 0, VarCategory::ERROR, 0), 
        ASTVar(0, 0, VarCategory::ERROR, 0), std::vector<ASTVar>(), nullptr)
{}

SubroutineManager::SubroutineStruct::SubroutineStruct(const SubroutineStruct& t_rBase) : 
    line(t_rBase.line), id(t_rBase.id), name(t_rBase.name), entryPoint(t_rBase.entryPoint),
    returnVar(
        (t_rBase.returnVar.nonBinary.getType() == TypeService::boolean)
        ? t_rBase.returnVar.binary
        : t_rBase.returnVar.nonBinary
    ), parameters(t_rBase.parameters), pBody(t_rBase.pBody)
{}

SubroutineManager::SubroutineStruct::SubroutineStruct(unsigned int t_line, SID t_id,
    const std::string& t_name, const ASTVar& t_entryPoint, const ASTVar& t_returnVar, 
    const std::vector<ASTVar>& t_parameters, ASTNode * const t_pBody) :
    line(t_line), id(t_id), name(t_name), entryPoint(t_entryPoint),
    returnVar(t_returnVar), parameters(t_parameters), pBody(t_pBody)
{}

SubroutineManager::SubroutineStruct::SubroutineStruct(unsigned int t_line, SID t_id,
    const std::string& t_name, const ASTVar& t_entryPoint, const ASTBoolVar& t_returnVar, 
    const std::vector<ASTVar>& t_parameters, ASTNode * const t_pBody) :
    line(t_line), id(t_id), name(t_name), entryPoint(t_entryPoint),
    returnVar(t_returnVar), parameters(t_parameters), pBody(t_pBody)
{}

SubroutineManager::SubroutineStruct::~SubroutineStruct()
{
    delete pBody;
}

const SubroutineManager::SubroutineStruct SubroutineManager::registerSubroutine(const std::string& t_name, 
    unsigned int t_referenceLine, TID t_returnType, const std::vector<TID>& t_params, 
    ASTNode * const t_pBodyRoot)
{
    const VID startId = VarReferencer::registerSubroutineVars(t_params.size());
    std::vector<ASTVar> params;
    for (unsigned int i = 0; i < t_params.size(); ++i)
    {
        params.emplace_back(
            t_referenceLine,
            t_params[i],
            VarCategory::SUBROUTINE,
            startId + 2 + i,
            false
        );
    }
    SID id = nextId++;
    std::string name = standardName(t_name, t_params);
    keyMap[name] = id;
    structMap.emplace(std::make_pair(id, SubroutineStruct{
        0, id, name, 
        ASTVar(t_referenceLine, TypeService::number, VarCategory::SUBROUTINE, 
            startId, false), 
        ((t_returnType == TypeService::boolean)
            ? ASTBoolVar(t_referenceLine, VarCategory::SUBROUTINE, startId + 1)
            : ASTVar(t_referenceLine, t_returnType, VarCategory::SUBROUTINE,
                startId + 1, false)),
        params,
        t_pBodyRoot}));
    return structMap[id];
}
    
SubroutineManager::SubroutineStruct SubroutineManager::getSubroutine(const std::string& t_name,
    const std::vector<TID>& t_params)
{
    return getSubroutine(keyMap[standardName(t_name, t_params)]);
}
SubroutineManager::SubroutineStruct SubroutineManager::getSubroutine(const SID t_id)
{
    return structMap[t_id];
}

const std::string printSub(const SubroutineManager::SubroutineStruct& t_rStruct)
{
    std::string rStr = t_rStruct.pBody->process();
    std::string entryPointVar = VarReferencer::getVarInfo(VarCategory::SUBROUTINE, 
        t_rStruct.entryPoint.ID).compiledName;
    if (lastLineLength(rStr) + 6 + entryPointVar.size() <= MAX_LINE_LENGTH)
    {
        rStr += " goto " + entryPointVar;
    } else {
        rStr += "\ngoto " + entryPointVar;
    }
    return rStr;
}

const std::string SubroutineManager::processSubroutine(const std::string& t_name,
    const std::vector<TID>& t_params)
{
    return printSub(getSubroutine(t_name, t_params));
}
const std::string SubroutineManager::processSubroutine(const SID t_id)
{
    return printSub(getSubroutine(t_id));
}