/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */
 
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
     * 显示窗口，但不激活
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
    NrWindowBase* m_pSendHandler {nullptr};
};

#endif
