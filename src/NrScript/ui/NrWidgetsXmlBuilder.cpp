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
