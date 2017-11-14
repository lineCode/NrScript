/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#ifndef _NRSCRIPT_NRAPPLICATIONOSWIN_H_
#define _NRSCRIPT_NRAPPLICATIONOSWIN_H_ 1

#include <windows.h>

/**
 * 应用程序类
 */
class NRSCRIPT_API_VISUAL NrApplicationOSWin {
public:
    /**
     * 退出程序
     */
    static int exit(const int exitCode);
};

#endif
