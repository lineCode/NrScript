/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"

NrChars NrString::toChars() const {
    char* buf = nullptr;

    size_t newCount = ::wcstombs(nullptr, *this, 0);
    if (newCount != -1) {
        buf = new char[newCount + 1]();
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

NrString NrChars::toString() const {
    wchar_t* buf = nullptr;

    size_t newCount = ::mbstowcs(nullptr, *this, 0);
    if (newCount != -1) {
        buf = new wchar_t[newCount + 1]();
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