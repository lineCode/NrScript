#include "NrBuilderFrame.h"
#include "NrBuilderApp.h"


NrBuilderApp::NrBuilderApp() {
}

NrBuilderApp::~NrBuilderApp() {
}

bool NrBuilderApp::initialize() {
    NrWindowBase::CreateParameter parameter {};
    parameter.bounds.width = 960;
    parameter.bounds.height = 544;
    parameter.caption = L"NrScript XML Builder";
    {
        NrString msg = L"中文编码测试";
        NrCharsUTF8 m2 = msg.toUTF8();
        parameter.caption = m2.toString();

        if (msg.equals(m2.toString())) {
            int i = 0;
        }
    }
    if (!m_builderFrame->create(parameter)) {
        return false;
    }
    m_builderFrame->show();
    return true;
}