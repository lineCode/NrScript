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

#ifndef _NRSCRIPT_NRXMLDOCUMENT_H_
#define _NRSCRIPT_NRXMLDOCUMENT_H_

enum class NrXmlParseStatus {
    /**
     * 文档解析成功，没有错误
     */
    Ok = 0,
    
    /**
     * loadFile错误，没有找到文件
     */
    FileNotFound,

    /**
     * 文件读取异常
     */
    IOError,

    /**
     * 内存不足，无法分配内存
     */
    OutOfMemory,

    /**
     * 内部错误
     */
    InternalError,
    
    /**
     * 解析器无法确认Tag类型
     */
    UnrecognizedTag,
    
    /**
     * 解析文档声明/处理指令时发生解析错误(Processing Instruction)
     */
    BadPI,

    /**
     * 解析注释时发生解析错误
     */
    BadComment,

    /**
     * 解析CDATA时发生解析错误
     */
    BadCDATA,

    /**
     * 解析文档类型声明时发生解析错误
     */
    BadDOCTYPE,

    /**
     * 解析PCDATA时发生解析错误
     */
    BadPCDATA,

    /**
     * 解析开始元素标记时发生解析错误
     */
    BadStartElement,

    /**
     * 解析元素属性时发生解析错误
     */
    BadAttribute,

    /**
     * 解析结束元素标记时发生解析错误
     */
    BadEndElement,

    /**
     * 开始结束标记不匹配（结束标记的名称不正确，某个标记未关闭或结尾标记过多）
     */
    EndElementMismatch,
    
    /**
     * 无法附加节点，因为根类型不是node_element或node_document（xml_node :: append_buffer专用）
     */
    AppendInvalidRoot,
    
    /**
     * 文档没有任何节点
     */
    NoDocumentElement,
};

/**
 * Xml文档编码
 */
enum class NrXmlEncoding {
    /**
     * 自动检测编码
     */
    Auto,

    UTF8,
    UTF16LE,
    UTF16BE,
    UTF16,
    UTF32LE,
    UTF32BE,
    UTF32,
    WCHAR,
    Latin1,
};

/**
 * xml文档解析结果
 */
struct NRSCRIPT_API_VISUAL NrXmlParseResult {
public:
    /**
     * 解析状态
     */
    NrXmlParseStatus status;
    
    /**
     * 解析偏移量
     */
    size_t offset;

    /**
     * 源文档编码
     */
    NrXmlEncoding encoding;

public:
    /**
     * 默认构造函数
     */
    NrXmlParseResult();
    
    /**
     * 运算符重载
     */
    operator bool() const;
    
    /**
     * 错误描述
     */
    NrString description() const;
};

/**
 * xml文档 (pugixml wrapper)
 */
class NRSCRIPT_API_VISUAL NrXmlDocument : public NrXmlNode {
public:
    /**
     * 默认构造函数
     */
    NrXmlDocument();

    /**
     * 赋值构造函数
     */
    NrXmlDocument(const NrXmlDocument& document);

    /**
     * 虚拟析构函数
     */
    virtual ~NrXmlDocument();

public:
    /**
     * 从字符串中加载
     */
    virtual NrXmlParseResult loadString(const NrString& xmlString);

    /**
     * 从文件中加载
     */
    virtual NrXmlParseResult loadFile(const NrString& filePath);

    /**
     * 从内存中读取
     */
    virtual NrXmlParseResult loadBuffer(const char* buffer, const size_t size);

    /**
     * 清除文档
     */
    virtual void clear();

    /**
     * NrXmlDocument对象拷贝
     */
    virtual NrXmlDocument& operator = (const NrXmlDocument& document);

    /**
     * 保存文件
     * @param [in] filePath 文件路径
     * @param [in] indent   缩进格式
     */
    virtual bool saveFile(const NrString& filePath, const typename NrString::char_t* indent = L"    ");

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
