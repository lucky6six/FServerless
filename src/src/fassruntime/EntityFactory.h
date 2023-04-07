#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "entity.h"

class EntityFactory {
public:
    static unordered_map<string, string> codeTable;
    EntityFactory();
    ~EntityFactory();
    bool entityCreate(string funcName, string code);
    void entityInterconnectEnable(Entity);
};

#endif // __ENTITYFACTORY_H__