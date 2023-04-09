#include "entity.h"



std::unordered_map<std::string,std::vector<Entity>> EntityTable::table;

std::unordered_map<std::string,int> EntityTable::funcCount;

EntityTable EntityTable::entityTable;
//tode
std::string Entity::entityRun(std::string para){
    std::string ret = "";
    if(ISOLATION == "DOCKER"){
        std::string ip = entityIp;
        ret = "docker ret" + entityIp;
    }
    return ret;
}

Entity::Entity(std::string ip){
    entityIp = ip;
}

Entity::Entity(){
}


Entity::~Entity(){

}

EntityTable::EntityTable(){
    // funcCount = new unordered_map<string,int>;
}

EntityTable::~EntityTable(){
    // delete funcCount;
}

bool EntityTable::isExist(std::string funcName){
    if(table.find(funcName)==table.end()){
        return 0;
    }else{
        return 1;
    }
    return 1;
}
bool EntityTable::bindEntity(std::string funcName,Entity entity){
    if(!isExist(funcName)){
        std::cout<<"error name when bind entity"<<std::endl;
        return 0;
    }
    // auto entityList = &(table.find(funcName)->second);

    // std::cout<<entity.entityIp<<std::endl;
    // entityList->push_back(entity);
    table.find(funcName)->second.push_back(entity);
    return 1;
}
Entity EntityTable::selectEntity(std::string funcName){
    Entity ret;
    if(!isExist(funcName)){
        std::cout<<"error funcName"<<std::endl;
        Entity r("no func");
        return r;
    }
    std::cout<<"funcName "<<funcName<<std::endl;
    auto entityList = table.find(funcName)->second;
    std::cout<<entityList.size()<<std::endl;
    if(entityList.size()==0){
        std::cout<<"no entity"<<std::endl;
        Entity r("no entity");
        return r;
    }
    if(ENTITY_INVOKE_STRATEGY == "DEFAULT"){
        int count = funcCount.find(funcName)->second;
        ret = entityList.at(count%entityList.size());
    }
    return ret;
}






