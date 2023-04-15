#include "os_shim.h"

int ExecuteCMD(const char *cmd, char *result)
{
    int ret;
    if(OS == "LINUX"||"WINDOWS"){
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
        ret = iRet;
    }
    

    return ret;
}
