/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"
#include <Windows.h>

NrChars NrString::toChars() const {
    char* buf = nullptr;

    /**
     * 如果这里第4个参数填写-1，则返回字符串长度+1(结尾'\0')，否则只返回字符串长度。
     * 但我们不用-1，需要手动添加一个'\0'长度
     */
    int newCount = ::WideCharToMultiByte(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0, nullptr, nullptr);
    if (newCount) {
        buf = new char[newCount + 1]();
    }

    if (buf) {
        if (::WideCharToMultiByte(CP_ACP, NULL, *this, static_cast<int>(this->length()), buf, newCount, NULL, NULL)) {
            buf[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    NrChars result = buf;
    delete buf;
    return result;
}

NrChars NrString::toUTF8() const {
    char* buf = nullptr;

    /**
     * 如果这里第4个参数填写-1，则返回字符串长度+1(结尾'\0')，否则只返回字符串长度。
     * 但我们不用-1，需要手动添加一个'\0'长度
     */
    int newCount = ::WideCharToMultiByte(CP_UTF8, 0, *this, static_cast<int>(this->length()), nullptr, 0, nullptr, nullptr);
    if (newCount) {
        buf = new char[newCount + 1]();
    }

    if (buf) {
        if (::WideCharToMultiByte(CP_UTF8, NULL, *this, static_cast<int>(this->length()), buf, newCount, NULL, NULL)) {
            buf[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    NrChars result = buf;
    delete buf;
    return result;
}

NrString NrChars::toString() const {
    wchar_t* buf = nullptr;

    int newCount = ::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0);
    if (newCount) {
        buf = new wchar_t[newCount + 1]();
    }

    if (buf) {
        if (::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), buf, newCount)) {
            buf[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    NrString result = buf;
    delete buf;
    return result;
}