#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
//todo 减少sleep
#include <unistd.h>
#include "config.h"
#include "os_shim.h"
#include <curl/curl.h>
// using namespace std;

class Entity{
    public:
        std::string entityIp;
        // string funcName;
        std::string entityRun(std::string para);
        // Entity(std::string ip);
        Entity();
        Entity(std::string funcName,std::string code,int ip);
        ~Entity();
};

class EntityTable{
    public:
        //funcName,entityIp
        static std::unordered_map<std::string,std::vector<Entity>> table;

        static std::unordered_map<std::string,int> funcCount;

        static EntityTable entityTable;
                   
        EntityTable();
        ~EntityTable();
        Entity selectEntity(std::string funcName);
        bool bindEntity(std::string funcName,Entity entity);
        bool isExist(std::string funcName);
};


#endif // __ENTITY_H__