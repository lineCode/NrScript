/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"
#include <codecvt>
#include <locale>

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

NrChars NrString::toUTF8() const {
    using utf8Converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>;

    utf8Converter conv;
    utf8Converter::byte_string bytes = conv.to_bytes(*this);

    NrChars retval {};
    if (!bytes.empty()) {
        retval = bytes.c_str();
    }
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