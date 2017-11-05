#ifndef _NRSCRIPT_NRXMLNODE_H_
#define _NRSCRIPT_NRXMLNODE_H_ 1

/**
 * xml节点
 */
class NRSCRIPT_API_VISUAL NrXmlNode {
public:
    /**
     * 默认构造函数
     */
    NrXmlNode();

    /**
     * 虚拟析构函数
     */
    virtual ~NrXmlNode();

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif //
