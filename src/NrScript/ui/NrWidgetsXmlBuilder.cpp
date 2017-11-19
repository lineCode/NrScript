#include "NrScript/base.h"
#include "NrScript/ui.h"

NrWidgetsXmlBuilder::NrWidgetsXmlBuilder() {
}

NrWidgetsXmlBuilder::~NrWidgetsXmlBuilder() {
    if (!m_creators.empty()) {
        for (auto i = m_creators.begin() ; i != m_creators.end() ; ++i) {
            i->second->destroy();
            i->second = nullptr;
        }
        m_creators.clear();
    }
}

NrWidgetsXmlBuilder & NrWidgetsXmlBuilder::instance() {
    static NrWidgetsXmlBuilder kBuiler;
    return kBuiler;
}

void NrWidgetsXmlBuilder::registerWidget(const NrString & widgetClassName, NrWidgetStringCreatorBase * creator) {
    if (!widgetClassName.isEmpty() && creator != nullptr) {
        if (!m_creators.insert(std::pair<NrString, NrWidgetStringCreatorBase*>(widgetClassName, creator)).second) {
        #ifdef NRSCRIPT_DEBUG
            NRSCRIPT_ASSERT("widget register failed!");
        #endif
        }
    }
}

NrControl * NrWidgetsXmlBuilder::ceateWidget(const NrString & name) {
    NrControl* retval = nullptr;
    
    if (name.isEmpty()) {
        return retval;
    }

    /**
     * 遍历creator创建控件
     */
    for (auto i = m_creators.begin() ; i != m_creators.end() ; ++i) {
        if (i->first.equals(name)) {
            retval = i->second->create();
            break;
        }
    }
    
    /**
     * 若用户关注了控件创建事件，则通知用户
     */
    if (!eOnCreateWidget.isEmpty()) {
        retval = eOnCreateWidget(name, retval);
    }
    return retval;
}