/**
 * NrScript Source Code File saved as UTF-8.bom format */

#ifndef _NRSCRIPT_NRSIMPLECHART_H_
#define _NRSCRIPT_NRSIMPLECHART_H_ 1

/**
 * 字符串容器
 */
template<typename T>
class NrSimpleCharTraitsBuf {
};

/**
 * 字符串
 */
template<typename T>
class NrSimpleCharT {
public:
    /**
     * 字符串类型
     */
    typedef T char_t;

    /** 
     * 用于标记查找目标字符串失败
     */
    static const size_t npos = (size_t) - 1;

public:
    /**
     * 默认构造函数
     */
    NrSimpleCharT() {
        m_data = new NrSimpleCharTraitsBuf<T>();
    }

    /**
     * 虚拟析构函数
     */
    virtual ~NrSimpleCharT() {
        delete m_data;
    }

public:
    /**
     * 确认字符串内容是否为空
     */
    bool isEmpty() const {
        return false;
    }

    /**
     * 确认指定字符串是否与当前内容一致
     */
    bool equals(const NrSimpleCharT<T>& source) const {
        source;
        return false;
    }

private:
    /**
     * 字符串数据
     */
    NrSimpleCharTraitsBuf<T>* m_data {nullptr};
};

/**
 * 模板接口导出
 */
template class NRSCRIPT_API_VISUAL NrSimpleCharT<wchar_t>;
template class NRSCRIPT_API_VISUAL NrSimpleCharT<char>;

/**
 * wchar_t字符串
 */
class NRSCRIPT_API_VISUAL NrString : public NrSimpleCharT<wchar_t> {
public:

};

/**
 * char 字符串
 */
class NRSCRIPT_API_VISUAL NrChars : public NrSimpleCharT<char> {
public:

};

#endif
