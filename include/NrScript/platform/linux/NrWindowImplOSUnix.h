#ifndef _NRSCRIPT_NRWINDOWIMPLOSUNIX_H_
#define _NRSCRIPT_NRWINDOWIMPLOSUNIX_H_ 1

#include <gtk/gtk.h>

/**
 * *nix平台窗口
 */
class NRSCRIPT_API_VISUAL NrWindowImplOSUnix : public NrWindowBase {
public:
    /**
     * 默认构造函数
     */
    NrWindowImplOSUnix(NrWindowBase* sendHandler);

    /**
     * 虚拟析构函数
     */
    virtual ~NrWindowImplOSUnix();

public:
    /**
     * 获取GTK窗口对象
     */
    GtkWidget* getWidget();

public:
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
     * 显示窗口，但不激活
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
    bool initialEvents();

private:
    /**
     * 窗口关闭事件
     */
    static bool kOnClose(GtkWidget *widget,GdkEvent *event, gpointer data);

    /**
     * 窗口销毁通知
     */
    static void kOnDestroy(GtkWidget *widget, gpointer data);

private:
    /**
     * 桥接
     */
    class Impl;
    Impl* impl {nullptr};

    /**
     * NrWindowImpl事件sender
     */
    NrWindowBase* m_pSendHandler;
};

#endif
