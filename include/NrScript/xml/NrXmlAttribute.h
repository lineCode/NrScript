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
 * !不要在此引入平台相关的头文件，
 */

#ifndef _NRSCRIPT_NRXMLATTRIBUTE_H_
#define _NRSCRIPT_NRXMLATTRIBUTE_H_ 1

class NRSCRIPT_API_VISUAL NrXmlAttribute {
public:
    /**
     * 默认构造函数
     */
    NrXmlAttribute();

    /**
     * 默认析构函数
     */
    virtual ~NrXmlAttribute();

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
