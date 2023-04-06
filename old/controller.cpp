#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "function.h"
#define BUFFSIZE 2048
#define DEFAULT_PORT 16555    // 指定端口为16555
#define MAXLINK 2048

using namespace std;

int sockfd, connfd;    // 定义服务端套接字和客户端套接字
void stopServerRunning(int p)
{
    close(sockfd);
    printf("Close Server\n");
    exit(0);
}
void setResponse(char *buff) {  
    string tmp = buff;
    bzero(buff, sizeof(buff)); 
    strcat(buff, "HTTP/1.1 200 OK\r\n"); 
    strcat(buff, "Connection: close\r\n"); 
    strcat(buff, "\r\n"); 
    strcat(buff, tmp.c_str());
}
int main()
{
    struct sockaddr_in servaddr;    // 用于存放ip和端口的结构
    char buff[BUFFSIZE];    // 用于收发数据
    // 对应伪代码中的sockfd = socket();
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        printf("Create socket error(%d): %s\n", errno, strerror(errno));
        return -1;
    }
    // END
    // 对应伪代码中的bind(sockfd, ip::port和一些配置);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);
    if (-1 == bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
        printf("Bind error(%d): %s\n", errno, strerror(errno));
        return -1;
    }
    // END
    // 对应伪代码中的listen(sockfd);    
    if (-1 == listen(sockfd, MAXLINK))
    {
        printf("Listen error(%d): %s\n", errno, strerror(errno));
        return -1;
    }
    // END
    printf("Listening...\n");
    while (true)
    {
        signal(SIGINT, stopServerRunning);
        connfd = accept(sockfd, NULL, NULL);
        if (-1 == connfd){
            printf("Accept error(%d): %s\n", errno, strerror(errno));
            return -1;
        }
        bzero(buff, BUFFSIZE);
        recv(connfd, buff, BUFFSIZE - 1, 0);
        //read commond
        string commond[20];
        string allcommond = buff;
        // //错误处理
        // cout << "111"<<allcommond<<"222" <<endl;
        // if(allcommond == ""||allcommond == " "){
        //     send(connfd, "error use", 20, 0);
        //     close(connfd);
        //     continue;
        // }
        int i = 0;
        while(allcommond!=""){
            commond[i] = allcommond.substr(0,allcommond.find(' '));
            i++;
            allcommond.erase(0,allcommond.find(' ')+1);
        }
        //createfunc name code
        if(commond[0]=="createfunc"){
            if(createFunc(commond[1],commond[2])){
                strcat(buff, "Create Success\r\n"); 
            }else{
                strcat(buff, "Create Failed\r\n");
            }
        }
        // //invoke name para 
        // if(commond[0]=="invoke"){
        //     string ret = invokeFunc(commond[1],commond[2]);
        // }

        // END
        setResponse(buff);
        printf("Recv: %s\n", buff);
        // 对应伪代码中的send(connfd, buff);
        send(connfd, buff, strlen(buff), 0);
        // END
        // 对应伪代码中的close(connfd);
        close(connfd);
        // END
    }
    return 0;
}