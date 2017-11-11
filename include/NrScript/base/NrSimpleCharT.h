/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

/** 字符串基本类型->确定只用char、wchar_t。char16_t、char32_t编码不在这里关心。

   关于wchar, char
  
   1> char
            ：实际测试中发现，char存储的是系统本地编码字符串，其二进制值不是固定的。有可能是GBK，也有可能是UTF-8(Linux)
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
          -> Windows不考虑了，直接使用 WideCharToMultiByte、 MultiByteToWideChar
          -> Linux
 */

#ifndef _NRSCRIPT_NRSIMPLECHART_H_
#define _NRSCRIPT_NRSIMPLECHART_H_ 1

/*******************************************************************************
 * 字符串容器
 */
template<typename T>
class NrSimpleCharTraitsBuf {
private:
    /**
     * template<typename char_t> class CharacterStorer {
     * public:
     *     typedef std::string str;
     * }
     *
     * template<> class CharacterStorer<wchar_t> {
     * public:
     *     typedef std::wstring str;
     * }
     *
     * ...
     *
     * error : explicit specialization in non-namespace scope
     * 类内部模板显示特化，msvc编译器支持，gcc不支持?...
     *
     */
    template<typename char_t, bool is_char = std::is_same<char_t, char>::value> class CharacterStorer {};
    template<typename char_t, bool is_wide = std::is_same<char_t, wchar_t>::value> class WideStorer {};
    template<typename char_t, bool is_char16 = std::is_same<char_t, char16_t>::value> class Char16Storer {};
    template<typename char_t, bool is_char32 = std::is_same<char_t, char32_t>::value> class Char32Storer {};

    template<typename char_t> class CharacterStorer<char_t, true> {
    public:
        typedef std::string str;
        typedef std::string::value_type value_type;
        typedef std::string::size_type size_type;
    };

    template<typename char_t> class CharacterStorer<char_t, false> {
    public:
        typedef typename WideStorer<char_t>::str str;
        typedef typename WideStorer<char_t>::value_type value_type;
        typedef typename WideStorer<char_t>::size_type size_type;
    };

    template<typename char_t> class WideStorer<char_t, true> {
    public:
        typedef std::wstring str;
        typedef std::wstring::value_type value_type;
        typedef std::wstring::size_type size_type;
    };

    template<typename char_t> class WideStorer<char_t, false> {
    public:
        typedef typename Char16Storer<char_t>::str str;
        typedef typename Char16Storer<char_t>::value_type value_type;
        typedef typename Char16Storer<char_t>::size_type size_type;
    };

    template<typename char_t> class Char16Storer<char_t, true> {
    public:
        typedef std::u16string str;
        typedef std::u16string::value_type value_type;
        typedef std::u16string::size_type size_type;
    };

    template<typename char_t> class Char16Storer<char_t, false> {
    public:
        typedef typename Char32Storer<char_t>::str str;
        typedef typename Char32Storer<char_t>::value_type value_type;
        typedef typename Char32Storer<char_t>::size_type size_type;
    };

    template<typename char_t> class Char32Storer<char_t, true> {
    public:
        typedef std::u32string str;
        typedef std::u32string::value_type value_type;
        typedef std::u32string::size_type size_type;
    };

    template<typename char_t> class Char32Storer<char_t, false> {
    public:
        typedef typename CharacterStorer<char>::str str;
        typedef typename CharacterStorer<char>::value_type value_type;
        typedef typename CharacterStorer<char>::size_type size_type;
    };

public:
    /**
     * 字符串存储类型
     */
    typedef typename CharacterStorer<T>::value_type char_t;

    /**
     * 存储空间size描述类型
     */
    typedef typename CharacterStorer<T>::size_type size_t;

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
    NrSimpleCharTraitsBuf<T>& operator = (const char_t* source) {
        if (source != nullptr) {
            (*m_value) = source;
        }
        return *this;
    }

public:
    /**
     * 访问字符串内存
     */
    operator const char_t* () const {
        return (*m_value).c_str();
    }

public:

    bool isEmpty() const {
        return (*m_value).empty();
    }

    bool equals(const NrSimpleCharTraitsBuf<T>& source) const {
        return (*m_value) == (*(source.m_value));
    }

    typename NrSimpleCharTraitsBuf<T>::size_t length() const {
        return (*m_value).length();
    }

private:
    /**
     * 初始化
     */
    void initialize() {
        m_value = new typename CharacterStorer<T>::str();
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
    typename CharacterStorer<T>::str* m_value {nullptr};
};

/*******************************************************************************/










/*******************************************************************************
 * 字符串 mutable
 */
template<typename T>
class NrSimpleCharT {
public:
    /**
     * 字符串类型
     */
    typedef typename NrSimpleCharTraitsBuf<T>::char_t char_t;

    /**
     * 存储空间size描述类型
     */
    typedef typename NrSimpleCharTraitsBuf<T>::size_t size_t;

    /** 
     * 用于标记查找目标字符串失败
     */
    static const typename NrSimpleCharT<T>::size_t npos = (NrSimpleCharT<T>::size_t) - 1;

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
    NrSimpleCharT(const char_t* source) {
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
    virtual NrSimpleCharT<T>& operator = (const char_t* source) {
        (*m_value) = source;
        return *this;
    }

public:
    /**
     * 访问字符串内存
     */
    operator const char_t*() const {
        return (*m_value);
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

    typename NrSimpleCharT<T>::size_t length() const {
        return (*m_value).length();
    }

public:


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
class NrChars;
class NrString;

template class NRSCRIPT_API_VISUAL NrSimpleCharT<char32_t>;
template class NRSCRIPT_API_VISUAL NrSimpleCharT<char16_t>;
template class NRSCRIPT_API_VISUAL NrSimpleCharT<wchar_t>;
template class NRSCRIPT_API_VISUAL NrSimpleCharT<char>;










/*******************************************************************************
 * wchar_t 字符串 mutable
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
    NrString(const typename NrString::char_t* source);

public:
    /**
     * 2. + 赋值运算符
     */
    NrString& operator = (const typename NrString::char_t* source) override;

public:
    /**
     * 转为 char 字符串 : 新建NrChars对象并将当前字符串内容存入其中
     *
     * @note linux使用前请确认当前程序已经使用 setlocale 设置区域信息
     *
     * TODO: 玄学
     * 
     * ->环境：Windows 10
     * ->地区：中国
     * ->语言：英文
     *
     * 在windows平台上 setlocale(LC_ALL, "")后，环境由 "C" 变为 "English_United States.1252"
     * 这时wcstombs并不能正确将含有"中文"的宽字节转为多字节.
     *
     * WideCharToMultiByte是怎么做到的?
     *
     *
     * TODO: 如果libNrScript.dll是静态链接运行时库，客户在主程序中调用
     *       setlocale 是否会忽略NrScript的运行时，无法正确修改NrScript的locale环境?
     */
    NrChars toChars() const ;
};










/*******************************************************************************
 * char 字符串 mutable
 * 不推荐使用，除非是调用系统API函数的时候。
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
    NrChars(const typename NrChars::char_t* source);

public:
    /**
     * 2. + 赋值运算符
     */
    NrChars& operator = (const typename NrChars::char_t* source) override;

public:
    /**
     * 转为 wchar_t 字符串 : 新建NrString对象并将当前字符串内容存入其中
     *
     * @note linux使用前请确认当前程序已经使用 setlocale 设置区域信息
     *
     * TODO: 如果libNrScript.dll是静态链接运行时库，客户在主程序中调用
     *       setlocale 是否会忽略NrScript的运行时，无法正确修改NrScript的locale环境?
     */
    NrString toString() const;
};

#endif
