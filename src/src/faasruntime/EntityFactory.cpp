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

Entity EntityFactory::entityCreate(string funcName,string code){
    Entity entity(funcName,code);
    return entity;
}

bool EntityFactory::entityNew(std::string funcName,std::string code){
    bool isok = false;
    std::string ip;
    Entity entity = entityCreate(funcName,code);
    if(entity.entityKey!=""){
        isok = true;
    }  
    // //tode
    // if(ISOLATION == "DOCKER"){
    //     std::cout<<"create success "<<code<<std::endl;
    //     isok = 1;
    //     ip = "1.1.1.1:1";
    //     entity.entityKey = ip;

    // }
    if(isok){
        if(EntityTable::entityTable.isExist(funcName)){
            cout<<"1"<<endl;
            EntityTable::entityTable.bindEntity(funcName,entity);
            cout<<"2"<<endl;
        }else{
            vector<Entity> tmp;
            cout<<"3"<<endl;
            EntityTable::entityTable.table.emplace(funcName,tmp);
            cout<<"4"<<endl;
            EntityTable::funcCount.emplace(funcName,0);
            cout<<"5"<<endl;
            EntityTable::entityTable.bindEntity(funcName,entity);
            cout<<"1"<<endl;
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