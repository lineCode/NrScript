#ifndef _NRSCRIPT_NRCONTROLRENDERMANAGER_H_
#define _NRSCRIPT_NRCONTROLRENDERMANAGER_H_ 1

/**
 * 控件渲染管理
 */
class NRSCRIPT_API_VISUAL NrWidgetsTreeRenderer {
public:
    /**
     * 默认构造函数
     */
    NrWidgetsTreeRenderer();
    
    /**
     * 析构函数
     */
    virtual ~NrWidgetsTreeRenderer();

    /**
     * 设置根节点，重新绘制
     */
    void doTraversal(int width, int height);

private:
    /**
     * 根节点控件
     */
    NrControl* m_root {nullptr};

    /**
     * 目标窗体客户区宽度
     */
    int m_hostWidth {0};

    /**
     * 目标窗体客户区高度
     */
    int m_hostHeight {0};
};

#endif
