/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : 1. NrScript库中所有char常量字符串(文字、符号)必须限定为英文 
 *        2. 与特定系统平台相关的代码，请放入platform目录中
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 */
 
#include "NrScript/base.h"
#include "NrScript/ui.h"
#include "NrScript/platform/linux/NrWindowImplOSUnix.h"
//#include "NrScript/skia.h"

class NrWindowImplOSUnix::Impl : public NrWindowBase {
public:
    /**
     * 默认构造函数
     */
    Impl(NrWindowImplOSUnix* owner): m_pOwner(owner) {
        m_renderer = new NrWidgetsTreeRenderer();
    }

    /**
     * 默认析构函数
     */
    ~Impl() {
        delete m_renderer;
    }

public:
    /**
     * 获取GTK窗口对象
     */
    GtkWidget* getWidget() {
        return m_widget;
    }

public:
    /**
     * 创建GTK窗口对象
     */
    bool create(const NrWindowBase::CreateParameter& parameter) override {
        static bool kNrScriptGtkWidgetInitialized = false;

        if (!kNrScriptGtkWidgetInitialized) {
            /**
             * 需要更新吗？
             */
            kNrScriptGtkWidgetInitialized = true;
        }

        m_widget = ::gtk_window_new(GTK_WINDOW_TOPLEVEL);
        if (m_widget == nullptr || !m_pOwner->initialEvents()) {
            return false;
        }

        /**
         * 这里需要显式地创建gdk资源. T.T
         * 不然在窗口没有显示之前，gdk资源没有与当前gtk资源绑定，一些操作无法生效！
         */
        ::gtk_widget_realize(m_widget);
        ::gtk_window_set_title(GTK_WINDOW(m_widget), parameter.caption.toUTF8());
        ::gtk_window_resize(GTK_WINDOW(m_widget), parameter.bounds.width, parameter.bounds.height);
        ::gtk_window_move(GTK_WINDOW(m_widget), parameter.bounds.x, parameter.bounds.y);

        return true;
    }

    void close() override {
        ::gtk_window_close(GTK_WINDOW(m_widget));
    }

    NrWindowBase* getNativeWindow() const override {
        return m_pOwner;
    }

    bool isActive() const override {
        return false;
    }

    bool isVisible() const override {
        return static_cast<bool>(::gtk_widget_is_visible(m_widget));
    }

    bool isDialog() const override {
        return m_isDialog;
    }

    void show() override {
        ::gtk_widget_show(m_widget);
    }

    void show(NrWindowBase* parent) override {
        NrWindowImplOSUnix* parentWidget = dynamic_cast<NrWindowImplOSUnix*>(parent->getNativeWindow());
        if (parentWidget && parentWidget != this->m_pOwner) {
            ::gtk_window_set_transient_for(GTK_WINDOW(m_widget), GTK_WINDOW(parentWidget->getWidget()));
        }
        this->show();
    }

    NrDialogResult showDialog(NrWindowBase* parent) override {
        NrWindowImplOSUnix* parentWidget = dynamic_cast<NrWindowImplOSUnix*>(parent->getNativeWindow());
        if (parentWidget == nullptr || parentWidget == this->m_pOwner) {
            return NrDialogResult::Exception;
        }

        if (this->isVisible()) {
            return NrDialogResult::Exception;
        }

        if (!::gtk_widget_is_sensitive(m_widget)) {
            return NrDialogResult::Exception;
        }

        if (this->isDialog()) {
            return NrDialogResult::Exception;
        }

        if (m_gtkDialogLoop == nullptr) {
            m_gtkDialogLoop = ::g_main_loop_new(NULL, FALSE);
        }

        if (m_gtkDialogLoop == nullptr) {
            return NrDialogResult::Exception;
        }

        /**
         * 准备模态显示
         */
        m_isDialog = true;
        m_dialogResult = NrDialogResult::None;

        GtkWindow* preOwner = ::gtk_window_get_transient_for(GTK_WINDOW(m_widget));
        gboolean preEnabled = ::gtk_widget_is_sensitive(parentWidget->getWidget());

        ::gtk_widget_set_sensitive(parentWidget->getWidget(), FALSE);
        ::gtk_window_set_modal(GTK_WINDOW(m_widget), TRUE);
        ::gtk_window_set_transient_for(GTK_WINDOW(m_widget), GTK_WINDOW(parentWidget->getWidget()));
        this->show();

        /**
         * 模态显示中
         */
        ::g_main_loop_run(m_gtkDialogLoop);

        ::gtk_widget_set_sensitive(parentWidget->getWidget(), preEnabled);
        ::gtk_window_set_transient_for(GTK_WINDOW(m_widget), preOwner);
        ::gtk_window_set_modal(GTK_WINDOW(m_widget), FALSE);

        m_isDialog = false;
        return m_dialogResult;
    }

    void setDialogResult(const NrDialogResult result) override {
        if (!isDialog()) {
            NRSCRIPT_ASSERT(false);
        }
        releaseDialogMessageLoop();

        this->m_dialogResult = result;
    }

    void showInactive() override {

    }

    void hide() override {
        if (isDialog()) {
            releaseDialogMessageLoop();
        }
        ::gtk_widget_hide(m_widget);
    }

    void setBounds(const NrRect& bounds) override {
        ::gtk_window_resize(GTK_WINDOW(m_widget), bounds.width, bounds.height);
        ::gtk_window_move(GTK_WINDOW(m_widget), bounds.x, bounds.y);
    }

    NrRect getBounds() const override {
        NrRect retval {};

        ::gtk_window_get_size(GTK_WINDOW(m_widget), &retval.width, &retval.height);
        ::gtk_window_get_position(GTK_WINDOW(m_widget), &retval.x, &retval.y);

        return retval;
    }

    /**
     * 11/08/2017 在Ubuntu17.10下无法gtk_window_move
     * TODO:不知道什么问题
     */
    void centerScreen() override {
        GdkRectangle area {};
        NrRect selfBounds {};
        gint tbWidth = 0;
        gint tbHeight = 0;

        GdkWindow*  pWindow  = ::gtk_widget_get_window(m_widget);
        GdkDisplay* pDisplay = ::gtk_widget_get_display(m_widget);
        GdkMonitor* pMonitor = ::gdk_display_get_monitor_at_window(pDisplay, pWindow);

        ::gdk_monitor_get_workarea(pMonitor, &area);
        selfBounds = getBounds();
        ::gdk_window_get_geometry(pWindow, &tbWidth, &tbHeight, nullptr, nullptr);

        int x = (area.width - selfBounds.width) / 2 - tbWidth;
        int y = (area.height - selfBounds.height) / 2 - tbHeight;

        ::gtk_window_resize(GTK_WINDOW(m_widget), selfBounds.width, selfBounds.height);
        ::gtk_window_move(GTK_WINDOW(m_widget), x, y);
    }

    void centerParent(const NrWindowBase* parent) {
        if (parent == nullptr) {
            NRSCRIPT_ASSERT(false);
            return;
        }

        NrWindowImplOSUnix* native = dynamic_cast<NrWindowImplOSUnix*>(parent->getNativeWindow());
        if (native == nullptr) {
            NRSCRIPT_ASSERT(false);
            return;
        }

        GdkWindow* pGdkWindow = ::gtk_widget_get_window(m_widget);
        NrRect selfBounds  = this->getBounds();
        NrRect ownerBounds = native->getBounds();

        int x = (ownerBounds.width - selfBounds.width) / 2;
        int y = (ownerBounds.height - selfBounds.height) / 2;

        ::gtk_window_resize(GTK_WINDOW(m_widget), selfBounds.width, selfBounds.height);
        ::gtk_window_move(GTK_WINDOW(m_widget), x + ownerBounds.x, y + ownerBounds.y);
    }

    void setContentView(NrControl* root) override {
        m_renderer->setRenderTarget(root);
    }

private:
    /**
     * 清理对话框消息循环对象
     */
    void releaseDialogMessageLoop() {
        if (m_gtkDialogLoop) {
            ::g_main_loop_quit(m_gtkDialogLoop);
            ::g_main_loop_unref(m_gtkDialogLoop);
            m_gtkDialogLoop = nullptr;
        }
    }

private:
    /**
     * GTK窗口对象
     */
    GtkWidget* m_widget {nullptr};

    /**
     * 桥接容器
     */
    NrWindowImplOSUnix* m_pOwner {nullptr};

    /**
     * 是否模态对话框模式
     */
    bool m_isDialog {false};

    /**
     * 对话框返回值
     */
    NrDialogResult m_dialogResult {NrDialogResult::None};

    /**
     * gtk dialog message loop
     */
    GMainLoop* m_gtkDialogLoop {nullptr};

    /**
     * 窗口渲染器
     */
    NrWidgetsTreeRenderer* m_renderer {nullptr};
};

NrWindowImplOSUnix::NrWindowImplOSUnix(NrWindowBase* sendHandler) {
#ifdef NRSCRIPT_DEBUG
    if (sendHandler == nullptr) {
        NRSCRIPT_ASSERT(false);
    }
#endif
    m_pSendHandler = sendHandler;
    impl = new Impl(this);
}

NrWindowImplOSUnix::~NrWindowImplOSUnix() {
    m_pSendHandler = nullptr;
    delete impl;
}

GtkWidget* NrWindowImplOSUnix::getWidget() {
    return dynamic_cast<NrWindowImplOSUnix::Impl*>(impl)->getWidget();
}

bool NrWindowImplOSUnix::create(const NrWindowBase::CreateParameter &parameter) {
    return impl->create(parameter);
}

void NrWindowImplOSUnix::close() {
    return impl->close();
}

NrWindowBase* NrWindowImplOSUnix::getNativeWindow() const {
    return impl->getNativeWindow();
}

bool NrWindowImplOSUnix::isActive() const {
    return impl->isActive();
}

bool NrWindowImplOSUnix::isVisible() const {
    return impl->isVisible();
}

bool NrWindowImplOSUnix::isDialog() const {
    return impl->isDialog();
}

void NrWindowImplOSUnix::show() {
    return impl->show();
}

void NrWindowImplOSUnix::show(NrWindowBase *parent) {
    return impl->show(parent);
}

void NrWindowImplOSUnix::showInactive() {
    return impl->showInactive();
}

void NrWindowImplOSUnix::hide() {
    return impl->hide();
}

NrDialogResult NrWindowImplOSUnix::showDialog(NrWindowBase *parent) {
    return impl->showDialog(parent);
}

void NrWindowImplOSUnix::setDialogResult(const NrDialogResult result) {
    return impl->setDialogResult(result);
}

void NrWindowImplOSUnix::setBounds(const NrRect &bounds) {
    return impl->setBounds(bounds);
}

NrRect NrWindowImplOSUnix::getBounds() const {
    return impl->getBounds();
}

void NrWindowImplOSUnix::setContentView(NrControl* root) {
    return impl->setContentView(root);
}

void NrWindowImplOSUnix::centerScreen() {
    return impl->centerScreen();
}

void NrWindowImplOSUnix::centerParent(const NrWindowBase *parent) {
    return impl->centerParent(parent);
}

/**
 * 私有函数，非桥接函数都在下面书写
 */

bool NrWindowImplOSUnix::initialEvents() {
    GtkWidget* widget = getWidget();

    if (!widget) {
        return false;
    }

    ::g_signal_connect(G_OBJECT(widget), "delete_event", G_CALLBACK(NrWindowImplOSUnix::kOnClose), this);
    ::g_signal_connect(G_OBJECT(widget), "destroy", G_CALLBACK(NrWindowImplOSUnix::kOnDestroy), this);

    /**
     * 触发onCreate事件
     */
	NrWindowBase::CommonEvents* pEvents = dynamic_cast<NrWindowBase::CommonEvents*>(m_pSendHandler);
	if (pEvents && !pEvents->eOnCreate.isEmpty()) {
		pEvents->eOnCreate(m_pSendHandler, 0);
	}

    return true;
}

bool NrWindowImplOSUnix::kOnClose(GtkWidget *widget, GdkEvent *event, gpointer data) {
    if (!data) {
        return true;
    }

    NrWindowImplOSUnix* self = (NrWindowImplOSUnix*)data;
    NrWindowBase::CommonEvents* pEvents = dynamic_cast<NrWindowBase::CommonEvents*>(self->m_pSendHandler);

    if (event->type == GDK_DELETE) {
        bool bCloseable = false;
        if (pEvents && !pEvents->eOnClose.isEmpty()) {
            pEvents->eOnClose(self->m_pSendHandler, bCloseable);
        }

        if (bCloseable) {
            if (self->isDialog()) {
                bCloseable = false;
                self->setDialogResult(NrDialogResult::None);
                self->hide();
            }
        }

        return bCloseable ? false : true;
    }
    return true;
}

void NrWindowImplOSUnix::kOnDestroy(GtkWidget *widget, gpointer data) {
    if (data == nullptr) {
        return;
    }

    NrWindowImplOSUnix* self = (NrWindowImplOSUnix*)data;
    NrWindowBase::CommonEvents* pEvents = dynamic_cast<NrWindowBase::CommonEvents*>(self->m_pSendHandler);

    if (pEvents && !pEvents->eOnDestroy.isEmpty()) {
        pEvents->eOnDestroy(self->m_pSendHandler, 0);
    }
}
