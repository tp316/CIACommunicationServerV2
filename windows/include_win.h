#ifndef INCLUDE_WIN_H_INCLUDE_
#define INCLUDE_WIN_H_INCLUDE_
#pragma comment(lib, "libprotobuf.lib")	                     // proto buf需要用到的动态链接库
#pragma comment(lib, "libprotobuf-lite.lib")	             // proto buf需要用到的动态链接库
#pragma comment(lib, "libprotoc.lib")	                     // proto buf需要用到的动态链接库
#pragma comment(lib, "SHP_A3.lib")	                         // proto buf需要用到的动态链接库
#pragma comment(lib, "libboost_regex-vc120-mt-sgd-1_58.lib") // proto buf需要用到的动态链接库

#include <Windows.h>
#include "shpa3api.h"                                        // 包含SynCTI驱动程序需要的头文件, 只能放在Windows.h头文件之后

#endif // !INCLUDE_WIN_H_INCLUDE_
