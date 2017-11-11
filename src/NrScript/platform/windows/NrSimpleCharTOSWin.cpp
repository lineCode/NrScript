/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"
#include <Windows.h>

NrChars NrString::toChars() {
    char* retval = nullptr;

    /**
     * 如果这里第4个参数填写-1，则返回字符串长度+1(结尾'\0')，否则只返回字符串长度。
     * 但我们不用-1，需要手动添加一个'\0'长度
     */
    int newCount = ::WideCharToMultiByte(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0, nullptr, nullptr);
    if (newCount) {
        retval = new char[newCount + 1]();
    }

    if (retval) {
        if (::WideCharToMultiByte(CP_ACP, NULL, *this, static_cast<int>(this->length()), retval, newCount, NULL, NULL)) {
            retval[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    return retval;
}

NrString NrChars::toString() {
    wchar_t* retval = nullptr;

    int newCount = ::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), nullptr, 0);
    if (newCount) {
        retval = new wchar_t[newCount + 1]();
    }

    if (retval) {
        if (::MultiByteToWideChar(CP_ACP, 0, *this, static_cast<int>(this->length()), retval, newCount)) {
            retval[newCount] = 0;
        }
    } else {
        NRSCRIPT_ASSERT(false);
    }

    return retval;
}