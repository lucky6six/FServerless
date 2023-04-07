#include "entity.h"

//tode
string Entity::entityRun(string para){
    string ret = "";
    if(ISOLATION == "DOCKER"){
        string ip = entityIp;
        ret = "docker ret";
    }
    return ret;
}

Entity::Entity(string ip){
    entityIp = ip;
}

Entity::~Entity(){

}

EntityTable::EntityTable(){
    table = new unordered_map<string,vector<Entity>>;
    // funcCount = new unordered_map<string,int>;
}

EntityTable::~EntityTable(){
    delete table;
    // delete funcCount;
}

bool EntityTable::isExist(string funcName){
    if(table.find(funcName)==table.end()){
        return 0;
    }else{
        return 1;
    }
    return 1;
}
bool EntityTable::bindEntity(string funcName,Entity entity){
    if(!isExist(funcName)){
        cout<<"error name when bind entity"<<endl;
        return 0;
    }
    auto entityList = table.find(funcName)->second;
    entityList.push_back(entity);
    return 1;
}
Entity EntityTable::selectEntity(string funcName){
    Entity ret;
    if(!isExist(funcName)){
        cout<<"error funcName"<<endl;
        Entity r("no func");
        return r;
    }
    auto entityList = table.find(funcName)->second;
    if(entityList.size()==0){
        cout<<"no entity"<<endl;
        Entity r("no entity")<<endl;
        return r;
    }
    if(ENTITY_INVOKE_STRATEGY == "DEFAULT"){
        int count = funcCount.find(funcName)->second;
        ret = entityList.at(count%entityList.size());
    }
    return ret;
}






