#ifndef INCLUDE_SYS_H_INCLUDE_
#define INCLUDE_SYS_H_INCLUDE_
#ifdef WIN32
#pragma comment(lib, "libprotobuf.lib")	                     // proto buf需要用到的动态链接库
#pragma comment(lib, "libprotobuf-lite.lib")	             // proto buf需要用到的动态链接库
#pragma comment(lib, "libprotoc.lib")	                     // proto buf需要用到的动态链接库
#pragma comment(lib, "SHP_A3.lib")	                         // proto buf需要用到的动态链接库
#pragma comment(lib, "ZookeeperDLL.lib")                     // proto buf需要用到的动态链接库
//#pragma comment(lib, "libboost_regex-vc120-mt-sgd-1_58.lib") // proto buf需要用到的动态链接库
#include <winsock2.h>
#include <Windows.h>
#include "shpa3api.h"                                        // 包含SynCTI驱动程序需要的头文件, 只能放在Windows.h头文件之后
#else
#include <netinet/in.h>
#include "shpa3api.h"                                        // 包含SynCTI驱动程序需要的头文件, 只能放在Windows.h头文件之后
#endif // WIN32

#endif // !INCLUDE_SYS_H_INCLUDE_
