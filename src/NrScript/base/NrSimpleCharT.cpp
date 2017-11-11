/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

#include "NrScript/base.h"

NrString::NrString() {
}

NrString::~NrString() {
}

/**
 * 2. - 赋值构造函数
 */
NrString::NrString(const wchar_t* source):
    NrSimpleCharT<wchar_t>(source) {
}

/**
 * 2. + 赋值运算符
 */
NrString& NrString::operator = (const wchar_t* source) {
    NrSimpleCharT<wchar_t>::operator = (source);
    return *this;
}










NrChars::NrChars() {
}

NrChars::~NrChars() {
}

/**
 * 2. - 赋值构造函数
 */
NrChars::NrChars(const char* source):
    NrSimpleCharT<char>(source) {
}

/**
 * 2. + 赋值运算符
 */
NrChars& NrChars::operator = (const char* source) {
    NrSimpleCharT<char>::operator = (source);
    return *this;
}