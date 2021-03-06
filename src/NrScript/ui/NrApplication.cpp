﻿/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : 1. NrScript库中所有char常量字符串(文字、符号)必须限定为英文 
 *        2. 与特定系统平台相关的代码，请放入platform目录中
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 * !不要在此引入平台相关的头文件，
 */

#include "NrScript/base.h"
#include "NrScript/ui/NrApplication.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include "NrScript/platform/linux/NrApplicationOSUnix.h"
#else
#include "NrScript/platform/windows/NrApplicationOSWin.h"
#endif

int NrApplication::exit(int exitCode) {
#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
    return NrApplicationOSUnix::exit(exitCode);
#else
    return NrApplicationOSWin::exit(exitCode);
#endif
}