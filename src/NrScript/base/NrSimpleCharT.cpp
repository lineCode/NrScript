/**
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
 * !不要在此引入平台相关的头文件，
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










NrCharsUTF8::NrCharsUTF8() {
}

NrCharsUTF8::~NrCharsUTF8() {
}

NrCharsUTF8::NrCharsUTF8(const typename NrCharsUTF8::char_t* source):
    NrSimpleCharT<typename NrCharsUTF8::char_t>(source){
}

NrCharsUTF8::NrCharsUTF8(const NrCharsUTF8& source):
    NrSimpleCharT<typename NrCharsUTF8::char_t>(source) {
}

NrCharsUTF8& NrCharsUTF8::operator = (const NrCharsUTF8& source) {
    NrSimpleCharT<typename NrCharsUTF8::char_t>::operator = (source);
    return *this;
}

NrCharsUTF8::operator const typename NrCharsUTF8::char_t* () const {
    return NrSimpleCharT<typename NrCharsUTF8::char_t>::operator const typename NrCharsUTF8::char_t*();
}