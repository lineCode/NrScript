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

#ifndef _NRSCRIPT_NRXMLNODE_H_
#define _NRSCRIPT_NRXMLNODE_H_ 1

/**
 * xml节点类型
 */
enum class NrXmlNodeType {
    /**
     * 空节点句柄
     */
    Null,

    /**
     * 一个文档树的绝对根
     */
    Document,

    /**
     * 元素标记,例如'<node />'
     */
    Element,

    /**
     * 普通字符数据,例如 '文本'
     */
    PCDATA,

    /**
     * 字符数据,例如'<![CDATA [text]]>'
     */
    CDATA,

    /**
     * 注释,例如<!-- comment -->
     */
    Comment,

    /**
     * 处理指令,例如'<?name?>'
     */
    PI,

    /**
     * 文档声明,例如'<?xml version ="1.0"?>'
     */
    Declaration,

    /**
     * 文档类型声明,例如'<!DOCTYPE doc>'
     */
    DOCTYPE,
};

/**
 * xml节点
 */
class NRSCRIPT_API_VISUAL NrXmlNode {
public:
    /**
     * 默认构造函数
     */
    NrXmlNode();

    /**
     * 虚拟析构函数
     */
    virtual ~NrXmlNode();

public:


private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif //
