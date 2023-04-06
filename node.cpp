#include"node.h"

NodeTable::NodeTable(){
    nodeList = new vector<node>;
    nodeList->push_back(WORKER1);
    nodeList->push_back(WORKER2);
}

NodeTable::~NodeTable(){
    delete nodeList;
}

node NodeTable::selectNode(){
    node ret;
    if(FUNC_CREATE_STRATEGY == "DEFAULT"){
        static int num = 0;
        ret = nodeList->at(num%nodeList->size());
        num++;
    }
    return ret;
}