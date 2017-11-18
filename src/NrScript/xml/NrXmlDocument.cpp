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

private:
    /**
     * pugixml文档句柄
     */
    pugi::xml_document* m_document {nullptr};
};



NrXmlDocument::NrXmlDocument() {
    impl = new Impl;
}

NrXmlDocument::~NrXmlDocument() {
    delete impl;
}

bool NrXmlDocument::loadString(const NrString& xmlString) {
    if (xmlString.isEmpty()) {
        return false;
    }
    return true;
}

bool NrXmlDocument::loadFile(const NrString& filePath) {
    if (filePath.isEmpty()) {
        return false;
    }
    return true;
}

bool NrXmlDocument::loadBuffer(const char* buffer) {
    if (buffer == nullptr) {
        return false;
    }
    return true;
}