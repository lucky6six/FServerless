#include "EntityFactory.h"

using namespace std;

std::unordered_map<std::string,std::string> EntityFactory::codeTable;

EntityFactory::EntityFactory(){
    // char result[CMD_RESULT_BUF_SIZE];
    // string cmd = "docker network create --subnet=173.50.0.0/24 fnet"; 
    // ExecuteCMD(cmd.data(), result);
}
EntityFactory::~EntityFactory(){
}

void EntityFactory::entityInterconnectEnable(Entity){
    std::cout<<"enable inter"<<std::endl;
}

Entity EntityFactory::entityCreate(string funcName,string code){
    ip++;
    Entity entity(funcName,code,ip);
    return entity;
}

bool EntityFactory::entityNew(std::string funcName,std::string code){
    bool isok = false;
    std::string ip;
    Entity entity = entityCreate(funcName,code);
    if(entity.entityIp!=""){
        isok = true;
    }  
    if(isok){
        if(EntityTable::entityTable.isExist(funcName)){
            EntityTable::entityTable.bindEntity(funcName,entity);
        }else{
            vector<Entity> tmp;
            EntityTable::entityTable.table.emplace(pair<string, vector<Entity>>{funcName, tmp});
            EntityTable::funcCount.emplace(pair<string,int>{funcName,0});
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