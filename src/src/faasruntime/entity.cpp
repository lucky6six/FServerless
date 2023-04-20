#include "entity.h"
#include <curl/curl.h>

#include <iostream>

#include <string.h>


std::unordered_map<std::string,std::vector<Entity>> EntityTable::table;

std::unordered_map<std::string,int> EntityTable::funcCount;

EntityTable EntityTable::entityTable;
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((std::string*)userdata)->append(ptr, nmemb);
    return nmemb;
}

//tode
std::string Entity::entityRun(std::string para){
    std::string ret = "";
    if(ISOLATION == "DOCKER"&&INTERCONNECTION == "HTTP"){
        // std::string url = ""; 
        // std::string cmd = "";
        // if(para != ""){
        //     url = "?para="+para;
        //     cmd = cmd + "docker exec -it " + entityIp +" bash -x -c \"curl localhost:8000?para="+ para +"\"";
        // }else{
        //     cmd = cmd + "docker exec -it " + entityIp +" bash -x -c \"curl localhost:8000\"";
        // }  
        // sleep(1);
        // url = url + "curl "+entityIp+":8000?para=" + para;
        // std::cout<<url<<std::endl;
        // //todo:curl请求
        // char result[CMD_RESULT_BUF_SIZE]={0};
        // memset(result,'\0',sizeof(result));
        // ExecuteCMD(cmd.data(), result);
        // printf("%s", result);
        // ret = result;
        CURL *curl;
        curl = curl_easy_init();
        CURLcode res;
        std::string tmp;
        std::string url = entityIp+":8000?para=" + para;
        // curl_easy_setopt(curl, CURLOPT_URL, url.data());
        // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf.data());

        std::string response_data;        
        //改回get请求
        curl_easy_setopt(curl, CURLOPT_POST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
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
    return ret;
}

Entity::Entity(std::string funcName,std::string code,int ip){
    std::cout<<funcName<<std::endl;
    std::cout<<code<<std::endl;
    if(ISOLATION == "DOCKER"){
        std::string funcImageFolder = DOCKER_IMAGES_INFO_PATH + funcName;
        std::string cmd = "";
        cmd =cmd + "mkdir " +funcImageFolder;
        char result[CMD_RESULT_BUF_SIZE]={0};
        std::cout<<cmd<<std::endl;
        ExecuteCMD(cmd.data(),result);
        cmd = "";
        //tode cp become mv
        cmd =cmd + "mv "+ DOCKER_DEMO_PATH + code + " "+DOCKER_IMAGES_INFO_PATH + funcName +"/main.py";
        std::cout<<cmd<<std::endl;
        ExecuteCMD(cmd.data(),result);
        cmd = "";
        cmd =cmd + "cp "+ DOCKER_DEMO_PATH+ "dockerfile " +  funcImageFolder;
        std::cout<<cmd<<std::endl;
        ExecuteCMD(cmd.data(),result);
        // cmd = "echo "+ func +"/dockerfile " + "ADD " 
        if(INTERCONNECTION == "HTTP"){
            cmd = "";
            cmd =cmd + "cp "+ DOCKER_DEMO_PATH +"Fhttp.py " +  funcImageFolder;
            std::cout<<cmd<<std::endl;
            ExecuteCMD(cmd.data(),result);  
        }
        cmd = "docker build -t "+funcName+" "+ funcImageFolder+"/.";
        std::cout<<cmd<<std::endl;
        ExecuteCMD(cmd.data(), result);
        memset(result,'\0',sizeof(result));
        std::string realIp = "173.50.0." + std::to_string(ip);
        cmd = "docker run -d --network fnet --ip " + realIp+" "+ funcName;
        ExecuteCMD(cmd.data(), result);
        entityIp = realIp;
        // entityIp = entityIp.substr(0,entityIp.length()-1);
        sleep(1);
    }
}
// Entity::Entity(std::string ip){
//     entityKey = ip;
// }

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

    // std::cout<<entity.entityKey<<std::endl;
    // entityList->push_back(entity);
    table.find(funcName)->second.push_back(entity);
    return 1;
}
Entity EntityTable::selectEntity(std::string funcName){
    Entity ret;
    // if(!isExist(funcName)){
    //     std::cout<<"error funcName"<<std::endl;
    //     Entity r("no func");
    //     return r;
    // }
    std::cout<<"funcName "<<funcName<<std::endl;
    auto entityList = table.find(funcName)->second;
    std::cout<<entityList.size()<<std::endl;
    if(entityList.size()==0){
        std::cout<<"no entity"<<std::endl;
        Entity r;
        return r;
    }
    if(ENTITY_INVOKE_STRATEGY == "DEFAULT"){
        int count = funcCount.find(funcName)->second;
        ret = entityList.at(count%entityList.size());
    }
    return ret;
}






