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
    HWND getHwnd();

public:
    /**
     * 设置渲染视图
     */
    virtual void setContentView(NrControl* root) override;
    
    /**
     * 创建窗口
     */
    virtual bool create(const NrWindowCreateParameter& parameter) override;

    /**
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() override;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const override;

    /**
     * 显示窗口
     */
    virtual void show() override;

    /**
     * 显示窗口但不激活
     */
    virtual void showInactive() override;

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
