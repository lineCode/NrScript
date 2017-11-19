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
#include "NrScript/xml/NrXmlNode.h"
#include "NrScript/xml/NrXmlDocument.h"
#include "pugixml/pugixml.hpp"

class NrXmlDocument::Impl {
public:
    Impl() {
        m_document = new pugi::xml_document();
    }

    ~Impl() {
        delete m_document;
    }

public:
    /**
     * 解析xml
     */
    NrXmlParseResult loadString(const NrString& xmlString) const {
        NrXmlParseResult result;

        pugi::xml_parse_result r = m_document->load_string(xmlString);
        result.status = static_cast<NrXmlParseStatus>(r.status);
        result.offset = r.offset;
        result.encoding = static_cast<NrXmlEncoding>(r.encoding);
        return result;
    }

    NrXmlParseResult loadFile(const NrString& filePath) const {
        NrXmlParseResult result;

        pugi::xml_parse_result r = m_document->load_file(filePath);
        result.status = static_cast<NrXmlParseStatus>(r.status);
        result.offset = r.offset;
        result.encoding = static_cast<NrXmlEncoding>(r.encoding);
        return result;
    }

    NrXmlParseResult loadBuffer(const char* buffer, const size_t size) const {
        NrXmlParseResult result;

        pugi::xml_parse_result r = m_document->load_buffer(buffer, size);
        result.status = static_cast<NrXmlParseStatus>(r.status);
        result.offset = r.offset;
        result.encoding = static_cast<NrXmlEncoding>(r.encoding);
        return result;
    }

public:
    /**
     * 清除文档内容
     */
    void clear() const {
        m_document->reset();
    }

    /**
     * 清除文档内容并从指定Document对象中拷贝数据
     */
    void reload(const NrXmlDocument& doc) const {
        m_document->reset(*(doc.impl->m_document));
    }

    /**
     * 保存至文件
     */
    bool saveFile(const NrString& filePath, const typename NrString::char_t* indent) const {
        return m_document->save_file(filePath, indent);
    }

public:
    /**
     * pugixml文档句柄
     */
    pugi::xml_document* m_document {nullptr};
};










/**
 * NrXmlDocument
 */
NrXmlDocument::NrXmlDocument() {
    impl = new Impl;
}

NrXmlDocument::NrXmlDocument(const NrXmlDocument& document) {
    impl = new Impl;
    impl->reload(document);
}

NrXmlDocument::~NrXmlDocument() {
    delete impl;
}

NrXmlParseResult NrXmlDocument::loadString(const NrString& xmlString) {
    return impl->loadString(xmlString);
}

NrXmlParseResult NrXmlDocument::loadFile(const NrString& filePath) {
    return impl->loadFile(filePath);
}

NrXmlParseResult NrXmlDocument::loadBuffer(const char* buffer, const size_t size) {
    return impl->loadBuffer(buffer, size);
}

void NrXmlDocument::clear() {
    return impl->clear();
}

NrXmlDocument& NrXmlDocument::operator=(const NrXmlDocument & document) {
    impl->reload(document);
    return *this;
}

bool NrXmlDocument::saveFile(const NrString & filePath, const typename NrString::char_t * indent) {
    return impl->saveFile(filePath, indent);
}










/**
 * NrXmlParseResult
 */
NrXmlParseResult::NrXmlParseResult():
    status(NrXmlParseStatus::InternalError),
    offset(0),
    encoding(NrXmlEncoding::Auto) {
}

NrXmlParseResult::operator bool() const {
    return status == NrXmlParseStatus::Ok;
}

NrString NrXmlParseResult::description() const {
    switch (status) {
    case NrXmlParseStatus::Ok:
        return L"No error";
    case NrXmlParseStatus::FileNotFound:
        return L"File was not found";
    case NrXmlParseStatus::IOError:
        return L"Error reading from file/stream";
    case NrXmlParseStatus::OutOfMemory:
        return L"Could not allocate memory";
    case NrXmlParseStatus::InternalError:
        return L"Internal error occurred";
    case NrXmlParseStatus::UnrecognizedTag:
        return L"Could not determine tag type";
    case NrXmlParseStatus::BadPI:
        return L"Error parsing document declaration/processing instruction";
    case NrXmlParseStatus::BadComment:
        return L"Error parsing comment";
    case NrXmlParseStatus::BadCDATA:
        return L"Error parsing CDATA section";
    case NrXmlParseStatus::BadDOCTYPE:
        return L"Error parsing document type declaration";
    case NrXmlParseStatus::BadPCDATA:
        return L"Error parsing PCDATA section";
    case NrXmlParseStatus::BadStartElement:
        return L"Error parsing start element tag";
    case NrXmlParseStatus::BadAttribute:
        return L"Error parsing element attribute";
    case NrXmlParseStatus::BadEndElement:
        return L"Error parsing end element tag";
    case NrXmlParseStatus::EndElementMismatch:
        return L"Start-end tags mismatch";
    case NrXmlParseStatus::AppendInvalidRoot:
        return L"Unable to append nodes: root is not an element or document";
    case NrXmlParseStatus::NoDocumentElement:
        return L"No document element found";
    default:
        return L"Unknown error";
    }
}
