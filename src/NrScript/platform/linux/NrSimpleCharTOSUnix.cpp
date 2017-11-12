/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"
#include <codecvt>
#include <locale>

/*******************************************************************************
 * linux、windows平台wchar转utf8兼容性处理
 *
 * 用于解决gcc在linux、windows平台上wchar所占字节长度不同引起的utf8转wchar问题
 */
template<typename wchar_t_platform, int size = sizeof(wchar_t_platform)>
struct __gcc_utf8_wchar_convert : public std::wstring_convert<std::codecvt_utf8<wchar_t_platform>> {
};

template<typename wchar_t_platform>
struct __gcc_utf8_wchar_convert<wchar_t_platform, 2> : std::wstring_convert<std::codecvt_utf8_utf16<wchar_t_platform>> {
};










NrChars NrString::toChars() const {
    typename NrChars::char_t* buf = nullptr;

    size_t newCount = ::wcstombs(nullptr, *this, 0);
    if (newCount != -1) {
        buf = new typename NrChars::char_t[newCount + 1]();
    }

    if (buf) {
        if (::wcstombs(buf, *this, this->length()) != -1) {
            buf[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    NrChars retval = buf;
    delete buf;
    return retval;
}

NrCharsUTF8 NrString::toUTF8() const {
    __gcc_utf8_wchar_convert<typename NrString::char_t> conv;
    __gcc_utf8_wchar_convert<typename NrString::char_t>::byte_string bytes = conv.to_bytes(*this);

    return NrCharsUTF8::fromUTF8Bytes(bytes.c_str());
}

NrString NrChars::toString() const {
    typename NrString::char_t* buf = nullptr;

    size_t newCount = ::mbstowcs(nullptr, *this, 0);
    if (newCount != -1) {
        buf = new typename NrString::char_t[newCount + 1]();
    }

    if (buf) {
        if (::mbstowcs(buf, *this, this->length()) != -1) {
            buf[newCount] = 0;
        }
    }
    else {
        NRSCRIPT_ASSERT(false);
    }

    NrString retval = buf;
    delete buf;
    return retval;
}










NrCharsUTF8 NrCharsUTF8::fromUTF8Bytes(const typename NrCharsUTF8::char_t* source) {
    return NrCharsUTF8(source);
}

NrString NrCharsUTF8::toString() const {
    /**
     * 在Linux平台下，gcc将wchar解释为4个字节，使用utf-32编码字符串
     * 在windows平台下，mingw环境中的gcc，将wchar解释为2个字节，使用utf-16编码字符串
     *
     * using utf8Converter = std::wstring_convert<std::codecvt_utf8<typename NrString::char_t>>;
     *
     * gcc在linux下使用codecvt_utf8<wchar_t>将utf8转为wchar没有问题
     * 但gcc(mingw)在windows下却要使用codecvt_utf8_utf16<wchar>才行。不然转换出来的数据端序不对。
     *
     * 而msvc使用codecvt_utf8<wchar>即可。这个我不知道谁做错了。。。
     *
     * 解决方法：__gcc_utf8_wchar_convert
     *
     * TODO: gcc使用codecvt_utf8_utf16看着也没问题（从utf16字面上理解）
     *       msvc使用codecvt_utf8<wchar_t>看着也没问题(从参数上理解)
     *
     */
    __gcc_utf8_wchar_convert<typename NrString::char_t> conv;
    __gcc_utf8_wchar_convert<typename NrString::char_t>::wide_string bytes = conv.from_bytes(*this);

    NrString retval{};
    if (!bytes.empty()) {
        retval = bytes.c_str();
    }
    return retval;
}