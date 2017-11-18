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

#ifndef _NRSCRIPT_NRWIDGETSCOMMONPROPERTIES_H_
#define _NRSCRIPT_NRWIDGETSCOMMONPROPERTIES_H_ 1

/**
 * 模板接口导出(warning:C4251)
 */
template class NRSCRIPT_API_VISUAL NrWidgetProperty<NrString>;
template class NRSCRIPT_API_VISUAL NrWidgetProperty<uint32_t>;
template class NRSCRIPT_API_VISUAL NrWidgetProperty<NrRect>;

/**
 * 控件通用属性
 */
class NRSCRIPT_API_VISUAL NrWidgetCommonProperties {
public:
    /**
     * 外边距
     */
    NrWidgetProperty<NrRect> propMargin;

    /**
     * 边框
     */
    NrWidgetProperty<NrRect> propBorder;

    /**
     * 内边距
     */
    NrWidgetProperty<NrRect> propPadding;

    /**
     * 内容区域
     */
    NrWidgetProperty<NrRect> propContent;

    /**
     * 控件大小
     * @remarks 控件大小包含border的大小
     */
    NrWidgetProperty<NrRect> propSize;

public:
    /**
     * 文本内容
     */
    NrWidgetProperty<NrString> propText;

    /**
     * 文本颜色
     */
    NrWidgetProperty<uint32_t> propNormalTextColor;

    /**
     * 获取鼠标焦点时的文本颜色
     */
    NrWidgetProperty<uint32_t> propHotTextColor;

    /**
     * 选中时文本颜色
     */
    NrWidgetProperty<uint32_t> prorSelectedTextColor;

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
