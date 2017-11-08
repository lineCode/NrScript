/**
 * NrScript Source Code File saved as UTF-8.bom format */

#ifndef _NRSCRIPT_NRWINDOWBASE_H_
#define _NRSCRIPT_NRWINDOWBASE_H_ 1

enum class NrDialogResult {
    /**
     * 此值表示对话框并没有正确显示，需要额外处理。
     */
    Exception = -1,
    
    /**
     * 此值表示对话框正在运行中或者已经隐藏
     */
    None    = 0,

    /**
     * 分别表示其字面意思
     */
    Ok      = 1,
    Cancel  = 2,
    About   = 3,
    Retry   = 4,
    Ignore  = 5,
    Yes     = 6,
    No      = 7,
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
    * 窗口创建参数
    */
    struct NRSCRIPT_API_VISUAL CreateParameter {
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

public:
    /**
     * Clang编译器警告
     */
    virtual ~NrWindowBase() {};

public:
    /**
     * 设置渲染视图
     */
    virtual void setContentView(NrControl* root) = 0;

    /**
     * 创建窗口
     */
    virtual bool create(const NrWindowBase::CreateParameter& parameter) = 0;

    /**
     * 关闭窗口
     */
    virtual void close() = 0;

    /**
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() = 0;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const = 0;

    /**
     * 当前窗口是否显示
     */
    virtual bool isVisible() const = 0;

    /**
     * 是否模态对话框形式
     */
    virtual bool isDialog() const = 0;

    /**
     * 显示窗口
     */
    virtual void show() = 0;

    /**
     * 作为指定窗口的子窗口显示
     * @param parent 父窗口
     */
    virtual void show(NrWindowBase* parent) = 0;

    /**
     * 作为模态对话框显示
     * @param parent 父窗口
     * @remarks 作为模态对话框的情况下，点击关闭按钮或者调用close，并不会真正的关闭
     * 窗口(DestroyWindow)，而是隐藏。
     */
    virtual NrDialogResult showDialog(NrWindowBase* parent) = 0;

    /**
     * 设置对话框返回值
     * @remarks 此函数将终止模态对话框显示
     */
    virtual void setDialogResult(NrDialogResult result) = 0;

    /**
     * 显示窗口、但不激活
     */
    virtual void showInactive() = 0;

    /**
     * 隐藏窗口
     */
    virtual void hide() = 0;

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
 * 模板接口导出(warning:C4251)
 */
template class NRSCRIPT_API_VISUAL NrEvent<void(NrWindowBase*, NrReserved)>;
template class NRSCRIPT_API_VISUAL NrEvent<void(NrWindowBase*, bool&)>;
template class NRSCRIPT_API_VISUAL NrEvent<void(NrWindowBase*, const NrRect&)>;

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
    /**
     * 窗口创建成功事件
     * @param 事件对象
     * @param 未定义
     */
    NrEvent<void(NrWindowBase*, NrReserved)> eOnCreate;

    /**
     * 窗口关闭事件
     * @param 事件对象
     * @param 确认窗口关闭
     */
    NrEvent<void(NrWindowBase*, bool&)> eOnClose;

    /**
     * 窗口销毁事件
     * @param 事件对象
     * @param 未定义
     */
    NrEvent<void(NrWindowBase*, NrReserved)> eOnDestroy;

    /**
     * 窗体大小变化事件
     * @param 事件对象
     * @param 窗体位置、客户区域大小
     */
    NrEvent<void(NrWindowBase*, const NrRect&)> eOnSize;
};

#endif
