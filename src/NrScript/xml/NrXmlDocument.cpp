/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
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

bool NrXmlDocument::loadString(const char* xmlString) {
    return false;
}

bool NrXmlDocument::loadFile(const char* filePath) {
    return false;
}

bool NrXmlDocument::loadBuffer(const char* buffer) {
    return false;
}