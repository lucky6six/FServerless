#include "EntityFactory.h"

using namespace std;

EntityFactory::EntityFactory(){
    entityTable = new EntityTable();
    funcCount = new unordered_map<string,int>();
    codeTable = new unordered_map<string,string>();
}

EntityFactory::~EntityFactory(){
    delete entityTable;
    delete funcCount;
    delete codeTable;
}

EntityFactory::entityInterconnectEnable(Entity){
    cout<<"enable inter"<<endl;
}

//return ip
bool EntityFactory::entityCreate(string funcName,string code){
    bool isok = 0;
    string ip;
    Entity* entity;
    //tode
    if(ISOLATION == "DOCKER"){
        cout<<"create success "<<code<<endl;
        isok = 1;
        ip = "1.1.1.1:1";
        entity = new Entity(ip);
    }
    if(isok){
        if(entityTable->isExist(funcName)){
            entityTable->bindEntity(funcName,entity);
        }else{
            vector<Entity> tmp;
            entityTable->table.emplace(funcName,tmp);
            funcCount.emplace(funcName,0);
            delete &tmp;
            entityTable->bindEntity(funcName,entity);
            codeTable.emplace(funcName,code);
        }
        entityInterconnectEnable(entity);
        cout<<"create success"<<endl;
    }else{
        cout<<"create failed"<<endl;
        return 0;
    }
    return 1;
}