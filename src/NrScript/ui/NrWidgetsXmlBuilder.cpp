/**
* NrScript Source Code File saved as UTF-8.bom format
*
* note : 1. NrScript��������char�����ַ���(���֡�����)�����޶�ΪӢ��
*        2. ���ض�ϵͳƽ̨��صĴ��룬�����platformĿ¼��
*
*
*
*
*
*
*
*
* !��Ҫ�ڴ�����ƽ̨��ص�ͷ�ļ���
*/

#include "NrScript/base.h"
#include "NrScript/ui.h"

NrWidgetsXmlBuilder::NrWidgetsXmlBuilder() {
}

NrWidgetsXmlBuilder::~NrWidgetsXmlBuilder() {

}

bool NrWidgetsXmlBuilder::registerWidget(const NrString & widgetClassName, NrWidgetStringCreatorBase * creator)
{
    if (widgetClassName.isEmpty()) {
        return false;
    }

    if (creator == nullptr) {
        return false;
    }

    return true;
}
