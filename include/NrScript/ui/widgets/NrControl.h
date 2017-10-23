#ifndef _NRSCRIPT_CONTROL_H_
#define _NRSCRIPT_CONTROL_H_ 1

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
