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

#ifndef _NRSCRIPT_NRXMLDOCUMENT_H_
#define _NRSCRIPT_NRXMLDOCUMENT_H_

/**
 * xml文档 (pugixml wrapper)
 */
class NRSCRIPT_API_VISUAL NrXmlDocument {
public:
    /**
     * 默认构造函数
     */
    NrXmlDocument();

    /**
     * 虚拟析构函数
     */
    virtual ~NrXmlDocument();

public:
    /**
     * 从字符串中加载
     */
    virtual bool loadString(const NrString& xmlString);

    /**
     * 从文件中加载
     */
    virtual bool loadFile(const NrString& filePath);

    /**
     * 从内存中读取
     */
    virtual bool loadBuffer(const char* buffer);

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
