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

#ifndef _NRSCRIPT_CONTROL_H_
#define _NRSCRIPT_CONTROL_H_ 1
#include "NrScript/ui/NrWidgetsXmlBuilder.h"

/**
 * 默认控件基类
 */
class NRSCRIPT_API_VISUAL NrControl : public NrWidgetCommonEvents,
                                      public NrWidgetCommonProperties {
    friend class NrControlLayerManager;
public:
    /**
     * 默认构造函数
     */
    NrControl();

    /**
     * 虚拟析构函数
     */
    virtual ~NrControl();

public:
    /**
     * 添加子控件
     */
    virtual void add(NrControl* control);

    /**
     * 删除子控件
     */
    virtual void remove(NrControl* control);

    /**
     * 获取父控件
     */
    virtual NrControl* getParent();

private:
    /**
     * 更新控件层级
     */
    void updateLayer(int layer);

    /**
     * 初始化
     */
    void initialize();

    /**
     * 释放资源
     */
    void finalize();

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
