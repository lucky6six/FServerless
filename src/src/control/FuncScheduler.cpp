#include "FuncScheduler.h"
#include <curl/curl.h>

#include <iostream>

#include <string.h>

using namespace std;

FuncScheduler::FuncScheduler() {
    // 记录worker节点信息。
    curl = curl_easy_init();
}

FuncScheduler::~FuncScheduler() {
    curl_easy_cleanup(curl);
}
// to do
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((std::string*)userdata)->append(ptr, nmemb);
    return nmemb;
}

string FuncScheduler::invoke(string funcName, string para, node targetNode) {
    // return funcName << " "<<para<<" "<<ip<<" runtime";

    // CURLcode res;
    // string tmp;
    // char url[100] = "";
    // if (curl) {
    //     strcat(url, ip.data());
    //     // todo port
    //     tmp = "/invoke";
    //     strcat(url, tmp.data());
    //     tmp = "?name=";
    //     strcat(url, tmp);
    //     // funcName
    //     strcat(url, funcName);
    //     tmp = "&para=";
    //     strcat(url, tmp);
    //     // para
    //     strcat(url, para);
    //     // cout<<url<<endl;
        

    // }

    // return res;
    // CURL *curl;
    CURLcode res;
    std::string tmp;
    std::string url = targetNode + "/invoke?name=" + funcName + "&para=" + para;
    // curl_easy_setopt(curl, CURLOPT_URL, url.data());
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf.data());

    std::string response_data;        
    //改回get请求
    curl_easy_setopt(curl, CURLOPT_POST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    cout<<url.data()<<endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    // response_data.find()
    return response_data;
    // return "ok";
}


node FuncScheduler::findNodeToCreate() {
    if (!strcmp(FUNC_CREATE_STRATEGY, "DEFAULT")) {
        return table.selectNode();
    }
}

CURLcode FuncScheduler::createEntity(string funcName, string code, node targetNode) {
    CURLcode res;
    string tmp;
    // char url[100] = "";
    // char buff[2048] = "";
    // // todo port
    // strcat(url, targetNode.data());
    // tmp = "/create";
    // strcat(url, tmp.data());
    // // funcName
    // strcat(buff, funcName.data());
    // tmp = " ";
    // strcat(buff, tmp.data());
    // // code
    // strcat(buff, code.data());

    std::string url = targetNode + "/create";
    std::string buf = funcName + " " + code;

    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf.data());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    return res;
}


bool FuncScheduler::bindFunc(string funcName, node targetNode) {
    auto list = FunctionTable::funcTable.registeredTable.find(funcName);
    list->second.push_back(targetNode);
    return 1;
}

// to do
node FuncScheduler::newEntityCreate(string funcName) {
    node targetNode;
    string code;
    if (!strcmp(FUNC_CREATE_STRATEGY, "DEFAULT")) {
        targetNode = findNodeToCreate();
        code = FunctionTable::funcTable.findCode(funcName);
        std::cout << "create " << funcName << " entity with code " << code << " in " << targetNode << endl;
        // createEntity(string funcName,string code,node ip)
        createEntity(funcName, code, targetNode);
        if (0) {
            return "";
        }
    }
    bindFunc(funcName, targetNode);
    return targetNode;
}

// 一定能找到（大不了创建）
node FuncScheduler::findNodeToInvoke(string funcName) {
    // 有服务，无entity,先创建entity
    node ret = FunctionTable::funcTable.selectNode(funcName);
    if (ret == "") {
        node targetNode = newEntityCreate(funcName);
        if (targetNode == "") {
            std::cout << "can't create the first entity" << endl;
            return "";
        } else {
            ret = targetNode;
        }
    }
    return ret;
}

string FuncScheduler::invokeFunc(string funcName, string para) {
    // 服务不存在
    if (!FunctionTable::funcTable.isExist(funcName)) {
        cout << "can't find this function" << endl;
        return "error";
    }
    string ret;
    if (!strcmp(FUNC_INVOKE_STRATEGY, "DEFAULT")) {
        node ip = findNodeToInvoke(funcName);
        ret = invoke(funcName, para, ip);
        // 自动扩容
        int num = (++FunctionTable::funcTable.funcInfoTable.find(funcName)->second.num);
        if (num % SCALE == 0) {
            cout<<"scale"<<endl;
            newEntityCreate(funcName);
        }
    }
    return ret;
}