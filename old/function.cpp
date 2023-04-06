// bool bindFunc(string name,string ip){
//     auto ret = registeredTable.find(name);
//     if(ret==registeredTable.end()){
//         // vector<string> tmp;
//         // tmp.push_back(ip);
//         // registeredTable.emplace(pair<string,vector<string>>{name,tmp});
//         cout<<"wrong function name"<<endl;
//         return 0;
//     }else{
//         // registeredTable[name].push_back(ip);
//         ret->second.push_back(ip);
//     }  
//     return 1;
// }

// bool registerFunc(string name){
//     bool ret = 1;
//     if(registeredTable.find(name)==registeredTable.end()){
//         vector<string> tmp;//默认为空
//         registeredTable.emplace(pair<string,vector<string>>{name,tmp});
//     }else{
//         // registeredTable[name].push_back(ip);
//         // ret->second.push_back(ip);
//         ret = 0;
//         cout <<"ERROR:Function Name Already Exist"<<endl;
//     }  
//     return ret;
// }

// bool createFunc(string name,string code){
//     // if(entityCreateStrategy==Warm){
//     //     createEntity()
//     // }
//     Function* func = new Function;
//     func->code = code;
//     func->name = name;
//     Function funct = *func;
//     funcTable.push_back(funct);
//     return registerFunc(name);
// }

// string findEntity(string name){

// }

// string invokeFunc(string name){
//     auto ret = findEntity(name);
//     if(ret == ""){
//         selectNode();
//         createEntity();
//         bindEntity();
//         findEntity();
//     }
//     selectEntity();
//     invokeEntity();
// }