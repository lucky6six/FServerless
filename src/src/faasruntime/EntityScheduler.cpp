#include "EntityScheduler.h"

using namespace std;

EntityScheduler::EntityScheduler(){

}

EntityScheduler::~EntityScheduler(){

}

Entity EntityScheduler::selectEntity(string funcName){
    Entity ret;
    if(ENTITY_INVOKE_STRATEGY == "DEFAULT"){
        ret = EntityTable::entityTable.selectEntity(funcName);
    }
    return ret;
}

string EntityScheduler::invokeEntity(string para,Entity entity){
    return entity.entityRun(para);
}

// string thread_invoke(string funcName,string para){}

string EntityScheduler::invokeFunc(string funcName,string para){
    if(!EntityTable::entityTable.isExist(funcName)){
        cout<<"error funcName"<<endl;
        return "error";
    }
    Entity entity = selectEntity(funcName);
    return entity.entityRun(para);
}