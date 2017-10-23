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
