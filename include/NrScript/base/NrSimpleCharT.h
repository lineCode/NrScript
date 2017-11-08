/**
 * NrScript Source Code File saved as UTF-8.bom format */

/** 字符串基本类型->确定只用char、wchar_t。char16_t、char32_t编码不在这里关心。

   关于wchar, char
  
   1> char
            不需要多解释，源码中的字符串对应出来的即ASCII字符集
            ：将GBK、BIG5这类只兼容ASCII却相互不兼容的编码统称之ASCII

   2> wchar
            在windows系统VC编译器里，wchar_t占两个字节，编译器将其解释存储为UTF-16LE(小端编码)。
                譬如： wchar_t ch = L'中'; 
                      ch的值为 0x4e2d ，这是 UTF-16LE 编码

            在Linux系统gcc编译器里，wchar_t占4个字节，编译器将其解释存储为UTF-32LE
                譬如： wchar_t ch = L'中';
                      ch的值为0x00004e2d，这是UTF-32LE 编码

            文件中的常量字符串不用担心编码。存储文件或读取文件时，注意转换即可保证跨平台文字乱码问题。
            例如 Windows 下将 UTF-8 格式的文件读取进行处理时，需要转为 UTF-16LE 编码(wchar_t)

    然而在UI、正则表达式处理上，无论用 char 还是用 wchar_t (UTF16或者UTF32)并不意味着可以
    将一个char、wchar_t代表一个字符，可以随意按wcslen(wchar_t*)的进行光标移动、正则处理。

    一头烦绪，先把NrString搞完后面搞NrEncoding这类东西。
 */

#ifndef _NRSCRIPT_NRSIMPLECHART_H_
#define _NRSCRIPT_NRSIMPLECHART_H_ 1

/**
 * 字符串容器
 */
template<typename T>
class NrSimpleCharTraitsBuf {
public:

private:
    /**
     * 字符串
     */
    T* m_data {nullptr};
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
