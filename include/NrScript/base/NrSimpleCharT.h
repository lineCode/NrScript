/**
 * NrScript Source Code File saved as UTF-8.bom format */

/** 字符串基本类型->确定只用char、wchar_t。char16_t、char32_t编码不在这里关心。

   关于wchar, char
  
   1> char
            不需要多解释，源码中的字符串对应出来的即ASCII字符集
            ：将GBK、BIG5这类只兼容ASCII却相互不兼容的地区性编码统称之ASCII

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

    TODO: char存储的字符串转为wchar是否需要考虑系统字符集? setlocale? 
 */

#ifndef _NRSCRIPT_NRSIMPLECHART_H_
#define _NRSCRIPT_NRSIMPLECHART_H_ 1

/*******************************************************************************
 * 字符串容器
 */
template<typename T>
class NrSimpleCharTraitsBuf {
private:
    template<typename char_t> class TraitsBuf {
    public:
        typedef std::string str;
    };

    template<> class TraitsBuf<wchar_t> {
    public:
        typedef std::wstring str;
    };

    template<> class TraitsBuf<char16_t> {
    public:
        typedef std::u16string str;
    };

    template<> class TraitsBuf<char32_t> {
    public:
        typedef std::u32string str;
    };

public:

    NrSimpleCharTraitsBuf() {
        this->initialize();
    }

    ~NrSimpleCharTraitsBuf() {
        this->finalize();
    }

public:
    /**
     * 1. 赋值运算符
     */
    NrSimpleCharTraitsBuf<T>& operator = (const NrSimpleCharTraitsBuf<T>& source) {
        (*m_value) = (*(source.m_value));
        return *this;
    }

    /**
     * 2. 赋值运算符
     */
    NrSimpleCharTraitsBuf<T>& operator = (const T* source) {
        (*m_value) = source;
        return *this;
    }

public:

    bool isEmpty() const {
        return (*m_value).empty();
    }

    bool equals(const NrSimpleCharTraitsBuf<T>& source) const {
        return (*m_value) == (*(source.m_value));
    }

private:
    /**
     * 初始化
     */
    void initialize() {
        m_value = new TraitsBuf<T>::str();
    }

    /**
     * 释放资源
     */
    void finalize() {
        delete m_value;
    }

private:
    /**
     * 字符串存储
     */
    typename TraitsBuf<T>::str* m_value {nullptr};
};

/*******************************************************************************/








/*******************************************************************************
 * 字符串 immutable
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
        this->initialize();
    }

    /**
     * 虚拟析构函数
     */
    virtual ~NrSimpleCharT() {
        this->finalize();
    }

public:
    /**
     * 1. - 赋值构造函数
     */
    NrSimpleCharT(const NrSimpleCharT<T>& source) {
        this->initialize();
        (*m_value) = (*(source.m_value));
    }

    /**
     * 2. - 赋值构造函数 
     */
    NrSimpleCharT(const T* source) {
        this->initialize();
        (*m_value) = source;
    }

public:
    /**
     * 1. + 赋值运算符
     */
    NrSimpleCharT<T>& operator = (const NrSimpleCharT<T>& source) {
        (*m_value) = (*(source.m_value));
        return *this;
    }

    /**
     * 2. + 赋值运算符
     */
    NrSimpleCharT<T>& operator = (const T* source) {
        (*m_value) = source;
        return *this;
    }

public:
    /**
     * 确认字符串内容是否为空
     */
    bool isEmpty() const {
        return (*m_value).isEmpty();
    }

    /**
     * 确认指定字符串是否与当前内容一致
     */
    bool equals(const NrSimpleCharT<T>& source) const {
        return (*m_value).equals(*source.m_value);
    }

private:
    /**
     * 初始化
     */
    void initialize() {
        m_value = new NrSimpleCharTraitsBuf<T>();
    }

    /**
     * 释放资源
     */
    void finalize() {
        delete m_value;
    }


private:
    /**
     * 字符串数据
     */
    NrSimpleCharTraitsBuf<T>* m_value {nullptr};
};










/*******************************************************************************
 * 模板接口导出
 */
template class NRSCRIPT_API_VISUAL NrSimpleCharT<wchar_t>;
template class NRSCRIPT_API_VISUAL NrSimpleCharT<char>;










/*******************************************************************************
 * wchar_t字符串 immutable
 */
class NRSCRIPT_API_VISUAL NrString : public NrSimpleCharT<wchar_t> {
public:
    /**
     * 默认构造函数
     */
    NrString();

    /**
     * 虚拟析构函数
     */
    virtual ~NrString();

public:
    /**
     * 2. - 赋值构造函数
     */
    NrString(const wchar_t* source);

public:
    /**
     * 2. + 赋值运算符
     */
    NrString& operator = (const wchar_t* source);
};










/*******************************************************************************
 * char 字符串 immutable
 */
class NRSCRIPT_API_VISUAL NrChars : public NrSimpleCharT<char> {
public:
    /**
     * 默认构造函数
     */
    NrChars();

    /**
     * 虚拟析构函数
     */
    virtual ~NrChars();

public:
    /**
     * 2. - 赋值构造函数
     */
    NrChars(const char* source);

public:
    /**
     * 2. + 赋值运算符
     */
    NrChars& operator = (const char* source);
};

#endif
