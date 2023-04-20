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

string EntityScheduler::invokeFunc(string funcName,string para){
    if(!EntityTable::entityTable.isExist(funcName)){
        cout<<"error funcName"<<endl;
        return "error";
    }
    Entity entity = selectEntity(funcName);
    return entity.entityRun(para);
}

size_t call_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((std::string*)userdata)->append(ptr, nmemb);
    return nmemb;
}


string EntityScheduler::callFunc(string funcName, string para){
    //Can this node provide this function？
    string ret;
    if(!EntityTable::entityTable.isExist(funcName)){
        if(INTERCONNECTION == "HTTP"){
            std::cout<<"by master"<<std::endl;
            CURL *curl;
            curl = curl_easy_init();
            CURLcode res;
            std::string tmp;
            std::string url;
            std::string response_data;   
            url = url + BASEURL + "invoke?name=" + funcName + "&para=" + para;
            //改回get请求
            curl_easy_setopt(curl, CURLOPT_POST, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_write_callback);
            std::cout<<url.data()<<std::endl;
            curl_easy_setopt(curl, CURLOPT_URL, url.data());
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            // response_data.find()
            curl_easy_cleanup(curl);
            std::cout<< response_data <<std::endl;
            ret = response_data;
        }
    }else{
        Entity entity = selectEntity(funcName);
        ret = entity.entityRun(para);
    }
    return ret;
}