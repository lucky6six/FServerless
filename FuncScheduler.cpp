#include "FuncScheduler.h"
#include <curl/curl.h>
using namespace std;



FuncScheduler::FuncScheduler(){
    //记录worker节点信息。
    table = new NodeTable();
    curl = curl_easy_init();
}

FuncScheduler::~FuncScheduler(){
    delete table;
    curl_easy_cleanup(curl);
}
//to do
string FuncScheduler::invoke(string funcName,string para,node ip){
    return funcName << " "<<para<<" "<<ip<<" runtime"; 
    CURLcode res;
    string tmp;
    char url[100]="";
    if(curl){
        strcat(url,ip);
        //todo port
        tmp = "/invoke";
        strcat(url,tmp);
        tmp = "?name=";
        strcat(url,tmp);
        //funcName
        strcat(url,funcName);
        tmp = "&para=";
        strcat(url,tmp);
        //para
        strcat(url,para);
        // cout<<url<<endl;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    }
    return res;
}




node FuncScheduler::findNodeToCreate(){
    if(FUNC_CREATE_STRATEGY=="DEFAULT"){
        return table.selectNode();
    }
}

CURLcode createEntity(string funcName,string code,node targetNode){
    CURLcode res;
    string tmp;
    char url[100]="";
    char buff[2048]="";
    //todo port
    strcat(url,targetNode);
    tmp = "/create";
    strcat(url,tmp);
    //funcName
    strcat(buff,funcName);
    tmp = " ";
    strcat(buff,tmp);
    //code
    strcat(buff,code);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buff);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    return res;
}


bool FuncScheduler::bindFunc(string funcName,node targetNode){
    auto list = funcTable->registeredTable->find(funcName);
    list->second.push_back(targetNode);
    return 1;
}

//to do
node FuncScheduler::newEntityCreate(string funcName){
    node targetNode;
    string code;
    if(FUNC_CREATE_STRATEGY=="DEFAULT"){
        targetNode = findNodeToCreate();
        code = funcTable->findCode(funcName);
        cout<<"create "<<funcName<<" entity with code "<<code<<" in "<<targetNode<<endl;
        //createEntity(string funcName,string code,node ip)
        createEntity(string funcName,string code,node targetNode);
        if(0){
        return "";
        }
    }
    bindFunc(funcName,targetNode);
    return targetNode;
}

//一定能找到（大不了创建）
node FuncScheduler::findNodeToInvoke(string funcName){
    //有服务，无entity,先创建entity
    node ret = funcTable->selectNode();
    if(ret==""){
        node targetNode = newEntityCreate(funcName);
        if(targetNode ==""){
            cout<<"can't create the first entity"<<endl;
            return "";
        }else{
            ret = targetNode;
        }
    }
    return ret;
}

string FuncScheduler::invokeFunc(string funcName,string para){
    //服务不存在
    if(!funcTable->isExist(funcName)){
        cout<<"can't find this function"<<endl;
        return "error";
    }
    string ret;
    if (FUNC_INVOKE_STRATEGY=="DEFAULT"){
        node ip = findNodeToInvoke(funcName);
        ret = invoke(funcName,para,ip);
        //自动扩容
        int num = (funcTable->funcInfoTable->find(funcName)->second.num++);
        if(num%SCALE = 0){
            newEntityCreate(funcName);
        }
    }
    return ret;
}