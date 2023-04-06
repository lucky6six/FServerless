#include "function.h"

using namespace std;

class FuncFactory{
    public:
        FuncFactory();
        ~FuncFactory();
        string functionCreate(string funcName, string code);
        bool functionSave(string funcName, Function func);
        bool functionRegister(string funcName);
        // //将创建的Function 信息存入注册表
        // bool registerFunc(string name);
};