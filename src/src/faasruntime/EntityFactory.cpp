#include "EntityFactory.h"

using namespace std;

std::unordered_map<std::string,std::string> EntityFactory::codeTable;

EntityFactory::EntityFactory(){
}
EntityFactory::~EntityFactory(){
}

void EntityFactory::entityInterconnectEnable(Entity){
    std::cout<<"enable inter"<<std::endl;
}
bool EntityFactory::entityCreate(std::string funcName,std::string code){
    bool isok = false;
    std::string ip;
    Entity entity;
    //tode
    if(ISOLATION == "DOCKER"){
        std::cout<<"create success "<<code<<std::endl;
        isok = 1;
        ip = "1.1.1.1:1";
        entity.entityIp = ip;
    }
    if(isok){
        if(EntityTable::entityTable.isExist(funcName)){
            EntityTable::entityTable.bindEntity(funcName,entity);
        }else{
            vector<Entity> tmp;
            EntityTable::entityTable.table.emplace(funcName,tmp);
            EntityTable::funcCount.emplace(funcName,0);
            delete &tmp;
            EntityTable::entityTable.bindEntity(funcName,entity);
            codeTable.emplace(funcName,code);
        }
        entityInterconnectEnable(entity);
        cout<<"create success"<<endl;
    }else{
        cout<<"create failed"<<endl;
        return false;
    }
    return true;
}