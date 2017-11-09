/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#ifndef _NRSCRIPT_NRAPPLICATION_H_
#define _NRSCRIPT_NRAPPLICATION_H_ 1

/**
 * 应用程序类
 */
class NRSCRIPT_API_VISUAL NrApplication {
private:
    /**
     * 默认构造函数
     */
    NrApplication() = default;

    /**
     * 析构函数
     */
    ~NrApplication() = default;

public:
    /**
     * 退出程序
     */
    static int exit(int exitCode);
};

#endif
