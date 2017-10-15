#ifndef _NRSCRIPT_STRING_H_
#define _NRSCRIPT_STRING_H_ 1

/**
 * char32_t字符串
 */
class NRSCRIPT_API_VISUAL NrString {
public:
    /**
     * 默认构造函数
     */
    NrString();

    /**
     * 虚拟析构函数
     */
    virtual ~NrString();

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
