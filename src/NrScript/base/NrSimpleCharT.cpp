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
NrString::NrString(const typename NrString::char_t* source):
    NrSimpleCharT<typename NrString::char_t>(source) {
}

/**
 * 2. + 赋值运算符
 */
NrString& NrString::operator = (const typename NrString::char_t* source) {
    NrSimpleCharT<typename NrString::char_t>::operator = (source);
    return *this;
}










NrChars::NrChars() {
}

NrChars::~NrChars() {
}

/**
 * 2. - 赋值构造函数
 */
NrChars::NrChars(const typename NrChars::char_t* source):
    NrSimpleCharT<typename NrChars::char_t>(source) {
}

/**
 * 2. + 赋值运算符
 */
NrChars& NrChars::operator = (const typename NrChars::char_t* source) {
    NrSimpleCharT<typename NrChars::char_t>::operator = (source);
    return *this;
}