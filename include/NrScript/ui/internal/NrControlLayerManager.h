#ifndef _NRSCRIPT_NRCONTROLLAYERMANAGER_H_
#define _NRSCRIPT_NRCONTROLLAYERMANAGER_H_ 1

/**
 * 控件管理，此类供NrWindow使用
 */
class NRSCRIPT_API_VISUAL NrControlLayerManager {
public:
    /**
     * 默认构造函数
     */
    NrControlLayerManager();
    
    /**
     * 虚拟析构函数
     */
    ~NrControlLayerManager();

public:
    /**
     * 从根节点开始更新控件层级
     */
    void update(NrControl* root);

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};
};

#endif
