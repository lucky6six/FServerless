#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#define BUFFSIZE 2048
#define PROXY "192.168.140.134:16555"    // 指定服务端的IP，记得修改为你的服务端所在的ip

using namespace std;

int main(int argc,char **argv)
{
    int i = 1;
    string tmp;
    string comm;
    while(i < argc){
        tmp = argv[i];
        comm.append(tmp);
        comm.push_back(' ');
        i++;
    }
    char buff[BUFFSIZE];
    strcpy(buff,comm.c_str());
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, PROXY);
        // cout<<buff<<endl;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buff);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}


// #include <sys/socket.h>
// #include <sys/unistd.h>
// #include <sys/types.h>
// #include <sys/errno.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// int main(int argc,char **argv)
// {
//     struct sockaddr_in servaddr;
//     char buff[BUFFSIZE];
//     //eg createFunction hello hello.py
//     string comm;
//     int i = 1;
//     string tmp;
//     while(i < argc){
//         tmp = argv[i];
//         comm.append(tmp);
//         comm.push_back(' ');
//         i++;
//     }
//     // string name = argv[2];
//     // string para = argv[3];
//     // comm.push_back(' ');
//     // comm.append(name);
//     // comm.push_back(' ');
//     // comm.append(para);
//     // comm.push_back(' ');


//     strcpy(buff,comm.c_str());
//     int sockfd;
//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if(-1 == sockfd)
//     {
//         printf("Create socket error(%d): %s\n", errno, strerror(errno));
//         return -1;
//     }
//     bzero(&servaddr, sizeof(servaddr));
//     servaddr.sin_family = AF_INET;
//     inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
//     servaddr.sin_port = htons(SERVER_PORT);
//     if (-1 == connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
//     {
//         printf("Connect error(%d): %s\n", errno, strerror(errno));
//         return -1;
//     }
//     // printf("Please input: ");
//     // scanf("%s", buff);
//     send(sockfd, buff, strlen(buff), 0);
//     bzero(buff, sizeof(buff));
//     recv(sockfd, buff, BUFFSIZE - 1, 0);
//     cout<<"rec "<<buff<<endl;
//     close(sockfd);
//     return 0;
// }