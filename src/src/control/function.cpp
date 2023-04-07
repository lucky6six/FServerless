#include "function.h"

#include <iostream>

using namespace std;

unordered_map<string, vector<node>> FunctionTable::registeredTable;

unordered_map<string, Function> FunctionTable::funcInfoTable;

FunctionTable FunctionTable::funcTable;

Function::Function(string a, string b, int c) {
    name = a;
    code = b;
    num = c;
}

Function::~Function() {
}


FunctionTable::FunctionTable() {
}

FunctionTable::~FunctionTable() {
}

bool FunctionTable::isExist(string funcName) {
    if (registeredTable.find(funcName) == registeredTable.end()) {
        return 0;
    }
    return 1;
}

node FunctionTable::selectNode(string funcName) {
    string ret;
    if (!isExist(funcName)) {
        ret = "error";
        return ret;
    }
    auto it = registeredTable.find(funcName);
    vector<node> nodeIps = it->second;
    if (nodeIps.size() == 0) {
        return "";
    }
    if (!strcmp(FUNC_INVOKE_STRATEGY, "DEFAULT")) {
        auto its = funcInfoTable.find(funcName);
        int num = its->second.num;
        ret = nodeIps.at(num % nodeIps.size());
    }
    return ret;
}

string FunctionTable::findCode(string funcName) {
    if (!isExist(funcName)) {
        return "";
    }
    auto its = funcInfoTable.find(funcName);
    return its->second.code;
}