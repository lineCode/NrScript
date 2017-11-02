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
    virtual bool loadString(const char* xmlString);

    /**
     * 从文件中加载
     */
    virtual bool loadFile(const char* filePath);

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
