#ifndef __CONFIG_H__
#define __CONFIG_H__

#define BASEURL "192.168.140.134:16555/" 
#define PORT 16555
#define PORTI 16666
#define MASTERIP "192.168.140.134"
#define WORKER1 "192.168.140.136:16555"
#define WORKER2 "192.168.140.137:16555"
// dafault means Polling轮询

#define FUNC_CREATE_STRATEGY "DEFAULT"
#define FUNC_INVOKE_STRATEGY "DEFAULT"
#define SCALE 1000//函数访问次数达到SCALE进行扩容

#define ISOLATION "DOCKER"
#define ENTITY_CREATE_STRATEGY "DEFAULT"
#define ENTITY_INVOKE_STRATEGY "DEFAULT"

#define OS "LINUX"
#define CMD_RESULT_BUF_SIZE 1024
// #define DOCKER_DEMO_PATH  "./dockerdemo/"
// #define DOCKER_IMAGES_INFO_PATH "./dockerConfig/"
#define DOCKER_DEMO_PATH  "/home/lz/Desktop/pro/FServerless/dockerdemo/"
#define DOCKER_IMAGES_INFO_PATH "/home/lz/Desktop/pro/FServerless/dockerConfig/"
#define INTERCONNECTION "HTTP"
#endif // __CONFIG_H__