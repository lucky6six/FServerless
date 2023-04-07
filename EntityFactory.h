#include "entity.h"

class EntityFactory{
    public:
        static unordered_map<string,string> codeTable;
        EntityFactory();
        ~EntityFactory();
        bool entityCreate(string funcName,string code);
        void entityInterconnectEnable(Entity);
};