#ifndef _NRSCRIPT_NRCONTROLRENDERMANAGER_H_
#define _NRSCRIPT_NRCONTROLRENDERMANAGER_H_ 1

/**
 * 控件渲染管理
 */
class NRSCRIPT_API_VISUAL NrControlRenderManager {
public:
    /**
     * 默认构造函数
     */
    NrControlRenderManager();
    
    /**
     * 析构函数
     */
    virtual ~NrControlRenderManager();

public:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
