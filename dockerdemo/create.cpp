#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <unistd.h>
// #include <fstream>
#define CMD_RESULT_BUF_SIZE 1024
#define DOCKER_DEMO_PATH  "/home/lz/Desktop/pro/FServerless/dockerdemo/"
#define DOCKER_IMAGES_INFO_PATH "/home/lz/Desktop/pro/FServerless/dockerConfig/"
int ExecuteCMD(const char *cmd, char *result)
{
    int iRet = -1;
    char buf_ps[CMD_RESULT_BUF_SIZE];
    char ps[CMD_RESULT_BUF_SIZE] = {0};
    FILE *ptr;

    strcpy(ps, cmd);

    if((ptr = popen(ps, "r")) != NULL)
    {
        while(fgets(buf_ps, sizeof(buf_ps), ptr) != NULL)
        {
           strcat(result, buf_ps);
           if(strlen(result) > CMD_RESULT_BUF_SIZE)
           {
               break;
           }
        }
        pclose(ptr);
        ptr = NULL;
        iRet = 0;  // 处理成功
    }
    else
    {
        printf("popen %s error\n", ps);
        iRet = -1; // 处理失败
    }

    return iRet;
}


int main()
{
    std::string funcName = "six.py";
    std::string func = DOCKER_IMAGES_INFO_PATH + funcName.substr(0,funcName.length()-3);
    std::string cmd = "";
    cmd =cmd + "mkdir " +func;
    char result[CMD_RESULT_BUF_SIZE]={0};
    ExecuteCMD(cmd.data(),result);
    cmd = "mv "+ funcName + " "+func +"/main.py";
    ExecuteCMD(cmd.data(),result);
    cmd = "cp /home/lz/Desktop/pro/FServerless/dockerdemo/dockerfile " +  func;
    ExecuteCMD(cmd.data(),result);
    // cmd = "echo "+ func +"/dockerfile " + "ADD " 
    cmd = "cp /home/lz/Desktop/pro/FServerless/dockerdemo/Fhttp.py " +  func;
    ExecuteCMD(cmd.data(),result);  

    cmd = "docker build -t "+funcName.substr(0,funcName.length()-3)+" "+ func+"/.";
    std::cout<<cmd<<std::endl;
    ExecuteCMD(cmd.data(), result);
    memset(result,'\0',sizeof(result));
    cmd = "docker run -d "+funcName.substr(0,funcName.length()-3);
    ExecuteCMD(cmd.data(), result);
    //得到key（id） of docker
    sleep(1);
    printf("%s", result);
    result[strlen(result)-1]='\0';
    cmd = "";
    cmd = cmd + "docker exec -it " + result +" bash -x -c \"curl localhost:8000\"";
    sleep(1);
    std::cout<<cmd<<std::endl;
    memset(result,'\0',sizeof(result));
    ExecuteCMD(cmd.data(), result);
    printf("%s", result);
    
    

    return 0;
}