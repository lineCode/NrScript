/**
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
 *        
 */

#include "NrScript/base.h"
#include "NrScript/platform/windows/NrApplicationOSWin.h"

int NrApplicationOSWin::exit(const int exitCode) {
    PostQuitMessage(exitCode);
    return exitCode;
}