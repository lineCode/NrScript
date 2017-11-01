#ifndef _NRSCRIPT_NRWINDOWIMPLOSWIN_H_
#define _NRSCRIPT_NRWINDOWIMPLOSWIN_H_ 1

#include <Windows.h>

/**
 * Window平台窗口
 */
class NRSCRIPT_API_VISUAL NrWindowImplOSWin : public NrWindowBase {
public:
    /**
     * 消息处理
     * @param handled 是否完全控制此消息，若为True，则以eOnMessage事件的返回值，作为窗口
     * 回调过程的返回值；如果为false，则在eOnMessage事件之后，调用DefWindowProc作为返回值
     */
    struct MESSAGE {
        HWND hWnd;
        UINT uMsg;
        WPARAM wParam;
        LPARAM lParam;
        bool handled;
    };

public:
    /**
     * 默认构造函数
     */
    NrWindowImplOSWin(NrWindowBase* sendHandler);
    
    /**
     * 虚拟析构函数
     */
    virtual ~NrWindowImplOSWin();

public:
    /**
     * 获取窗口句柄
     */
    HWND getHwnd() const;

public:
    /**
     * 设置渲染视图
     */
    virtual void setContentView(NrControl* root) override;
    
    /**
     * 创建窗口
     */
    virtual bool create(const NrWindowBase::CreateParameter& parameter) override;

    /**
     * 关闭窗口
     */
    virtual void close() override;

    /**
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() override;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const override;

    /**
     * 当前窗口是否显示
     */
    virtual bool isVisible() const override;

    /**
     * 是否模态对话框形式
     */
    virtual bool isDialog() const override;

    /**
     * 显示窗口
     */
    virtual void show() override;

    /**
     * 作为指定窗口的子窗口显示
     * @param parent 父窗口
     */
    virtual void show(NrWindowBase* parent) override;

    /**
     * 作为模态对话框显示
     * @param parent 父窗口
     * @remarks 作为模态对话框的情况下，点击关闭按钮或者调用close，并不会真正的关闭
     * 窗口(DestroyWindow)，而是隐藏。
     */
    virtual NrDialogResult showDialog(NrWindowBase* parent) override;

    /**
     * 设置对话框返回值
     * @remarks 此函数将终止模态对话框显示
     */
    virtual void setDialogResult(NrDialogResult result) override;

    /**
     * 显示窗口但不激活
     */
    virtual void showInactive() override;

    /**
     * 隐藏窗口
     */
    virtual void hide() override;

    /**
     * 设置窗口位置、客户区大小
     */
    virtual void setBounds(const NrRect& bounds) override;

    /**
     * 获取窗口位置、客户区大小
     */
    virtual NrRect getBounds() const override;

private:
    /**
     * 事件初始化
     */
    void initialEvents();

    /**
     * 清理事件
     */
    void finalizeEvents();

    /**
     * 窗口回调过程. 参考MSDN
     */
    LRESULT handleMessage(HWND hWNd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    /**
     * 窗口回调事件
     */
    LRESULT OnMessage(NrWindowImplOSWin* sender, MESSAGE& msg);
    
public:
    /**
     * Windows消息循环事件
     * @param [in] MESSAGE  消息参数
     */
    NrEvent<LRESULT(NrWindowImplOSWin*, MESSAGE&)>* eOnMessagePtr;

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};

    /**
     * NrWindowImpl事件参数sender
     */
    NrWindowBase* m_pSendHandler {nullptr};
};

#endif
