#include <string>
#include <unordered_map>
#include <vector>
#include "node.h"
#include "config.h"
using namespace std;

class Function{
    public:
        // int id;//remind
        string name;//函数名
        string code;//代码段或代码文件（可能使用）
        int num;//调用次数
        // string file;//代码文件
        Function(string name,string code, int num);
        ~Function();
};
//全局唯一，全局变量
class FunctionTable{
    public:
        //funcname & nodeip
        static unordered_map<string,vector<node>> *registeredTable;
        //funcname & code
        static unordered_map<string,Function> *funcInfoTable;
        FunctionTable();
        //是否存在目标function
        bool isExist(string funcName);
        //when to invoke
        node selectNode(string funcName);//for invoke,不会找不到？
        string findCode(string funcName);
        // bool saveCode(string funcName, string code);
        // bool functionBind(string funcName, node ip);
        ~FunctionTable();
};

extern FunctionTable* funcTable;




