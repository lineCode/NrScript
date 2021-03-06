﻿/**
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
 *        
 */

#include "NrScript/base.h"
#include <Windows.h>
//#include <codecvt>
//#include <locale>

NrChars NrString::toChars() const {
    typename NrChars::char_t* buf = nullptr;
    NrChars retval;

    /**
     * 如果这里第4个参数填写-1，则返回字符串长度+1(结尾'\0')，否则只返回字符串长度。
     * 但我们不用-1，需要手动添加一个'\0'长度
     */
    const int newCount = ::WideCharToMultiByte(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0, nullptr, nullptr);
    if (newCount) {
        buf = new typename NrChars::char_t[newCount + 1]();
    }

    if (buf) {
        if (::WideCharToMultiByte(CP_ACP, NULL, *this, static_cast<int>(this->length()), buf, newCount, NULL, NULL)) {
            buf[newCount] = 0;
            retval = buf;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    if (buf != nullptr) {
        delete[] buf;
    }
    return retval;
}

NrCharsUTF8 NrString::toUTF8() const {

//#ifdef NRSCRIPT_DEBUG
//    using utf8Converter = std::wstring_convert<std::codecvt_utf8<typename NrString::char_t>>;
//
//    utf8Converter conv;
//    utf8Converter::byte_string bytes = conv.to_bytes(*this);
//
//    return NrCharsUTF8::fromUTF8Bytes(bytes.c_str());
//#endif

    typename NrCharsUTF8::char_t* buf = nullptr;
    NrCharsUTF8 retval;

    const int newCount = ::WideCharToMultiByte(CP_UTF8, 0, *this, static_cast<int>(this->length()), nullptr, 0, nullptr, nullptr);
    if (newCount) {
        buf = new typename NrCharsUTF8::char_t[newCount + 1]();
    }

    if (buf) {
        if (::WideCharToMultiByte(CP_UTF8, NULL, *this, static_cast<int>(this->length()), buf, newCount, NULL, NULL)) {
            buf[newCount] = 0;
            retval = NrCharsUTF8::fromUTF8Bytes(buf);
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    if (buf != nullptr) {
        delete[] buf;
    }
    return retval;
}

NrString NrChars::toString() const {
    typename NrString::char_t* buf = nullptr;
    NrString retval;

    const int newCount = ::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0);
    if (newCount) {
        buf = new typename NrString::char_t[newCount + 1]();
    }

    if (buf) {
        if (::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), buf, newCount)) {
            buf[newCount] = 0;
            retval = buf;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    if (buf != nullptr) {
        delete[] buf;
    }
    return retval;
}











NrCharsUTF8 NrCharsUTF8::fromUTF8Bytes(const typename NrCharsUTF8::char_t* source) {
    return NrCharsUTF8(source);
}

NrString NrCharsUTF8::toString() const {

//#ifdef NRSCRIPT_DEBUG
//    using utf8Converter = std::wstring_convert<std::codecvt_utf8<typename NrString::char_t>>;
//
//    utf8Converter conv;
//    utf8Converter::wide_string bytes = conv.from_bytes(*this);
//
//    NrString retval{};
//    if (!bytes.empty()) {
//        retval = bytes.c_str();
//    }
//    return retval;
//#endif

    typename NrString::char_t* buf = nullptr;
    NrString retval;

    const int newCount = ::MultiByteToWideChar(CP_UTF8, 0, *this, static_cast<int>(this->length()), nullptr, 0);
    if (newCount) {
        buf = new typename NrString::char_t[newCount + 1]();
    }

    if (buf) {
        if (::MultiByteToWideChar(CP_UTF8, 0, *this, static_cast<int>(this->length()), buf, newCount)) {
            buf[newCount] = 0;
            retval = buf;
        }
    }
    else {
        NRSCRIPT_ASSERT(false);
    }

    if (buf != nullptr) {
        delete[] buf;
    }
    return retval;
}