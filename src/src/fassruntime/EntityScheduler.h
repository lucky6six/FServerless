#ifndef __ENTITYSCHEDULER_H__
#define __ENTITYSCHEDULER_H__

#include "entity.h"

using namespace std;

class EntityScheduler {
public:
    EntityScheduler();
    ~EntityScheduler();
    Entity selectEntity(string funcName);
    string invokeEntity(string para, Entity entity);
    string invokeFunc(string funcName, string para);
};
#endif // __ENTITYSCHEDULER_H__