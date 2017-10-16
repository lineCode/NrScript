#ifndef _NRSCRIPT_NRWINDOWBASE_H_
#define _NRSCRIPT_NRWINDOWBASE_H_ 1

/**
 * 窗口创建参数
 */
struct NRSCRIPT_API_VISUAL NrWindowCreateParameter {
public:
    /**
     * 窗口标题
     */
    NrString caption;

    /**
     * 窗口位置、客户区域大小
     */
    NrRect bounds;
};

/**
 * 窗口操作接口
 */
class NRSCRIPT_API_VISUAL NrWindowBase {
public:
    /**
     * 窗口通用事件
     */
    class NRSCRIPT_API_VISUAL CommonEvents;

    /**
     * 渲染目标
     */
    class NRSCRIPT_API_VISUAL RenderTarget;

public:
    /**
     * Clang编译器警告
     */
    virtual ~NrWindowBase() {};

    /**
     * 创建窗口
     */
    virtual bool create(const NrWindowCreateParameter& parameter) = 0;

    /**
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() = 0;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const = 0;

    /**
     * 显示窗口
     */
    virtual void show() = 0;

    /**
     * 显示窗口、但不激活
     */
    virtual void showInactive() = 0;

    /**
     * 设置窗口位置、客户区大小
     */
    virtual void setBounds(const NrRect& bounds) = 0;

    /**
     * 获取窗口位置、客户区大小
     */
    virtual NrRect getBounds() const = 0;

//    /**
//     * 确认当前窗口是否最大化
//     */
//    virtual bool isMaximized() const = 0;
//
//    /**
//     * 确认当前窗口是否最小化
//     */
//    virtual bool isMinimized() const = 0;
//
//    /**
//     * 确认当前窗口是否全屏
//     */
//    virtual bool isFullscreen() const = 0;
//
//    /**
//     * 获取当前窗口元句柄
//     */
//    virtual void* GetNativeWindow() const = 0;
//
//
//
//
//    /**
//     * 隐藏窗口
//     */
//    virtual void hide() = 0;
//

//
//    /**
//     * 关闭窗口
//     */
//    virtual void close() = 0;
//
//    /**
//     * 激活窗口并前置(若最小化则需要显示出来)
//     */
//    virtual void activate() = 0;
//
//    /**
//     * 取消激活状态、并将Z-order下的窗口前置
//     */
//    virtual void deactivate() = 0;
//
//    /**
//     * 窗口最大化
//     */
//    virtual void maximize() = 0;
//
//    /**
//     * 窗口最小化
//     */
//    virtual void minimize() = 0;
//
//    /**
//     * 窗口恢复
//     */
//    virtual void restore() = 0;



//    /**
//     * 确认窗口是否始终置顶
//     */
//    virtual bool isAlwaysOnTop() const = 0;
//
//    /**
//     * 设置窗口置顶
//     */
//    virtual void setAlwaysOnTop(bool alwaysOnTop) = 0;

//    virtual bool isRestored() = 0;
//
//    /**
//     * 窗口恢复
//     */
//    virtual void restore() = 0;
};


/**
 * 窗口通用事件
 */
class NRSCRIPT_API_VISUAL NrWindowBase::CommonEvents {
public:
    /**
     * 默认构造函数
     */
    CommonEvents();

    /**
     * 默认析构函数
     */
    virtual ~CommonEvents();

public:
    NrEvent<void(NrWindowBase*, NrReserved)>* eOnCreatePtr;
    NrEvent<void(NrWindowBase*, bool&)>* eOnClosePtr;
    NrEvent<void(NrWindowBase*, NrReserved)>* eOnDestroyPtr;

    /**
     * 窗体大小变化事件
     * @param 事件对象
     * @param 窗体位置、客户区域大小
     */
    NrEvent<void(NrWindowBase*, const NrRect&)>* eOnSizePtr;
};

class NRSCRIPT_API_VISUAL NrWindowBase::RenderTarget {
public:
    /**
     * Clang编译警告
     */
    virtual ~RenderTarget() {};

    /**
     * 遍历渲染
     */
    virtual void norityTraversalsRender(const int width, const int height) = 0;
};

#endif
