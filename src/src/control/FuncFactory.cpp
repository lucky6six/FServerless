#include "FuncFactory.h"

using namespace std;

FuncFactory::FuncFactory() {
}

FuncFactory::~FuncFactory() {
}

bool FuncFactory::functionRegister(string funcName) {
    vector<node> tmp;
    FunctionTable::funcTable.registeredTable.emplace(pair<string, vector<node>>{funcName, tmp});
    return 1;
}

bool FuncFactory::functionSave(string funcName, Function func) {
    FunctionTable::funcTable.funcInfoTable.emplace(pair<string, Function>{funcName, func});
    return 1;
}

string FuncFactory::functionCreate(string funcName, string code) {
    if (FunctionTable::funcTable.isExist(funcName)) {
        return "name has existed";
    }
    Function *func = new Function(funcName, code, 0);
    functionRegister(funcName);
    functionSave(funcName, *func);
    delete func;
    return "function " + funcName + " create";
}