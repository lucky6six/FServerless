#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#define CMD_RESULT_BUF_SIZE 1024
/*
 * cmd：待执行命令
 * result：命令输出结果
 * 函数返回：0 成功；-1 失败；
 */
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
    char result[CMD_RESULT_BUF_SIZE]={0};
    char cmd[CMD_RESULT_BUF_SIZE]={0};
    ExecuteCMD("docker build -t dockertest .", result);
    memset(result,'\0',sizeof(result));
    ExecuteCMD("docker run -d dockertest", result);
        printf("%s", result);
    strcat(cmd,"docker exec -it ");
    result[strlen(result)-1]='\0';
    strcat(cmd,result);
    char tmp[CMD_RESULT_BUF_SIZE]={0};
    sleep(1);
    strcat(cmd," bash -x -c \"curl localhost:8000\"");
    // strcat(cmd," bash -x -c \"echo hello world\"");
    std::cout<<cmd<<std::endl;
    memset(result,'\0',sizeof(result));
    ExecuteCMD(cmd, result);
    printf("%s", result);

    return 0;
}