#ifndef FUNCSCHEDULER_H
#define FUNCSCHEDULER_H

#include <curl/curl.h>

#include "function.h"

using namespace std;

class FuncScheduler {
public:
    NodeTable table;
    CURL *curl;

    FuncScheduler();
    ~FuncScheduler();

    // 1.无服务 ->error 2. 有服务无node ->first create 3.返回node
    node findNodeToInvoke(string funcName); // select in functiontable
    string invokeFunc(string funcName, string para);
    string invoke(string funcName, string para, node ip);
    node findNodeToCreate(); // select in nodetable
    // 创建某一节点的第一个entity
    node newEntityCreate(string funcName);
    // 将node的ip在Functiontable进行绑定
    bool bindFunc(string funcName, node ip);

    CURLcode createEntity(string funcName, string code, node targetNode);
};

#endif // FUNCSCHEDULER_H
