#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

class function{
    public:
        int id;//remind
        string name;//函数名
        string code;//代码段或代码文件（可能使用）
        string file;//代码文件
};
//函数与实体注册表
static vector<function> funcTable;
static unordered_map<string,vector<string>> registeredTable;
//将创建的Function 信息存入注册表
bool registerFunc(string name);
// //将Entity的ip与Function进行绑定
// bool bindFunc(string name,string ip);

//根据函数名与代码创建function
bool createFunc(string name,string code);


// // string selectNode()

// string findEntity(string name);
// string invokeFunc(string name,string para);