#ifndef _NRSCRIPT_NRWIDGETSCOMMONPROPERTIES_H_
#define _NRSCRIPT_NRWIDGETSCOMMONPROPERTIES_H_ 1

/**
 * 模板接口导出(warning:C4251)
 */
template class NRSCRIPT_API_VISUAL NrWidgetProperty<NrString>;
template class NRSCRIPT_API_VISUAL NrWidgetProperty<uint32_t>;

/**
 * 控件通用属性
 */
class NRSCRIPT_API_VISUAL NrWidgetCommonProperties {
public:
    /**
     * 文本内容
     */
    NrWidgetProperty<NrString> propText;

    /**
     * 文本颜色
     */
    NrWidgetProperty<uint32_t> propTextColor;

    /**
     * 文本字体大小
     */
    NrWidgetProperty<uint32_t> propTextSize;

    /**
     * 文本字体
     */
    NrWidgetProperty<NrString> propTextFont;
};

#endif
