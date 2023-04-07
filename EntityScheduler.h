#include "entity.h"

using namespace std;

class EntityScheduler{
    public:
        EntityScheduler();
        ~EntityScheduler();
        Entity selectEntity(string funcName);
        string invokeEntity(string para,Entity entity);
        string invokeFunc(string funcName,string para);
};