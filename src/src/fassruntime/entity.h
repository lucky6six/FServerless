#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <unordered_map>
#include <vector>
#include <string>
#include "config.h"
#include <iostream>
using namespace std;

class Entity{
    public:
        string entityIp;
        // string funcName;
        string entityRun(string para);
        Entity(string ip);
        ~Entity();
};

class EntityTable{
    public:
        //funcName,entityIp
        static unordered_map<string,vector<Entity>> table;
        
        EntityTable();
        ~EntityTable();
        Entity selectEntity(string funcName);
        bool bindEntity(string funcName,Entity entity);
        bool isExist(string funcName);
};

extern EntityTable* entityTable;
extern unordered_map<string,int> funcCount;

#endif // __ENTITY_H__