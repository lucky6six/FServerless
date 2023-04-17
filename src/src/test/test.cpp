// #include <stdio.h>
// #include <string.h>
// #include <iostream>
// #include <unistd.h>
// #define CMD_RESULT_BUF_SIZE 1024
// /*
//  * cmd：待执行命令
//  * result：命令输出结果
//  * 函数返回：0 成功；-1 失败；
//  */
// int ExecuteCMD(const char *cmd, char *result)
// {
//     int iRet = -1;
//     char buf_ps[CMD_RESULT_BUF_SIZE];
//     char ps[CMD_RESULT_BUF_SIZE] = {0};
//     FILE *ptr;

//     strcpy(ps, cmd);

//     if((ptr = popen(ps, "r")) != NULL)
//     {
//         while(fgets(buf_ps, sizeof(buf_ps), ptr) != NULL)
//         {
//            strcat(result, buf_ps);
//            if(strlen(result) > CMD_RESULT_BUF_SIZE)
//            {
//                break;
//            }
//         }
//         pclose(ptr);
//         ptr = NULL;
//         iRet = 0;  // 处理成功
//     }
//     else
//     {
//         printf("popen %s error\n", ps);
//         iRet = -1; // 处理失败
//     }

//     return iRet;
// }

// int main()
// {
//     char result[CMD_RESULT_BUF_SIZE]={0};
//     char cmd[CMD_RESULT_BUF_SIZE]={0};
//     ExecuteCMD("docker build -t dockertest .", result);
//     memset(result,'\0',sizeof(result));
//     ExecuteCMD("docker run -d dockertest", result);
//         printf("%s", result);
//     strcat(cmd,"docker exec -it ");
//     result[strlen(result)-1]='\0';
//     strcat(cmd,result);
//     char tmp[CMD_RESULT_BUF_SIZE]={0};
//     sleep(1);
//     strcat(cmd," bash -x -c \"curl localhost:8000\"");
//     // strcat(cmd," bash -x -c \"echo hello world\"");
//     std::cout<<cmd<<std::endl;
//     memset(result,'\0',sizeof(result));
//     ExecuteCMD(cmd, result);
//     printf("%s", result);

//     return 0;
// }
#include <curl/curl.h>

#include <iostream>

#include <string.h>
using namespace std;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((std::string*)userdata)->append(ptr, nmemb);
    return nmemb;
}


int main(){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode res;
    std::string tmp;
    std::string url = "172.12.0.3:8000";
    // curl_easy_setopt(curl, CURLOPT_URL, url.data());
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf.data());

    std::string response_data;        
    //改回get请求
    curl_easy_setopt(curl, CURLOPT_POST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    cout<<url.data()<<endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    // response_data.find()
    curl_easy_cleanup(curl);
    cout<< response_data <<endl;
    return 0;
}
   