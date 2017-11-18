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

#ifndef _NRSCRIPT_NRWIDGETSCOMMONEVENTS_H_
#define _NRSCRIPT_NRWIDGETSCOMMONEVENTS_H_ 1

class NRSCRIPT_API_VISUAL NrControl;

/**
 * 事件模板接口导出
 */
template class NRSCRIPT_API_VISUAL NrEvent<void(NrControl*, NrString)>;
template class NRSCRIPT_API_VISUAL NrEvent<void(NrControl*, NrReserved)>;

/**
 * 控件通用事件
 */
class NRSCRIPT_API_VISUAL NrWidgetCommonEvents {
public:
    /**
     * 控件通用事件
     */
    NrEvent<void(NrControl*, NrReserved)> eOnPaint;

    /**
     * 控件属性值改变事件
     * @param 控件对象
     * @param 属性名称
     */
    NrEvent<void(NrControl*, NrString)> eOnPropertyChange;
};

#endif
