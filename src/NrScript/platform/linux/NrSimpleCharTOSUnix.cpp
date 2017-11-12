/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"
#include <codecvt>
#include <locale>

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
    using utf8Converter = std::wstring_convert<std::codecvt_utf8<typename NrString::char_t>>;

    utf8Converter conv;
    utf8Converter::byte_string bytes = conv.to_bytes(*this);

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
    using utf8Converter = std::wstring_convert<std::codecvt_utf8<typename NrString::char_t>>;

    utf8Converter conv;
    utf8Converter::wide_string bytes = conv.from_bytes(*this);

    NrString retval{};
    if (!bytes.empty()) {
        retval = bytes.c_str();
    }
    return retval;
}