#include "NrScript/base.h"
#include "NrScript/xml/NrXmlAttribute.h"

class NrXmlAttribute::Impl {
    
};










/**
 * NrXmlAttribute
 */
NrXmlAttribute::NrXmlAttribute() {
    impl = new Impl();
}

NrXmlAttribute::~NrXmlAttribute() {
    delete impl;
}
