#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "entity.h"

class EntityFactory {
public:
    static std::unordered_map<std::string,std::string> codeTable;
    EntityFactory();
    ~EntityFactory();
    Entity entityCreate(std::string funcName, std::string code);
    bool entityNew(std::string funcName, std::string code);
    void entityInterconnectEnable(Entity);
};

#endif // __ENTITYFACTORY_H__