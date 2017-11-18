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
 
#ifndef _NRSCRIPT_NRAPPLICATIONOSUNIX_H_
#define _NRSCRIPT_NRAPPLICATIONOSUNIX_H_ 1

#include <gtk/gtk.h>

/**
 * 应用程序类
 */
class NRSCRIPT_API_VISUAL NrApplicationOSUnix {
public:
    /**
     * 退出程序
     */
    static int exit(const int exitCode);
};

#endif
