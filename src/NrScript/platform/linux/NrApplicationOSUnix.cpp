/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */
 
#include "NrScript/base.h"
#include "NrScript/platform/linux/NrApplicationOSUnix.h"

int NrApplicationOSUnix::exit(int exitCode) {
    ::gtk_main_quit();
    return exitCode;
}