#ifndef __OS_SHIM_H__
#define __OS_SHIM_H__

#include <stdio.h>
#include <string.h>
#include <string>

#include "config.h"
//shell操作与结果读取的封装
int ExecuteCMD(const char *cmd, char *result);

//todo 内存封装

//todo 数据库封装
#endif // __OS_SHIM_H__