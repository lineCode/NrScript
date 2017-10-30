#include "NrScript/base.h"
#include "NrScript/ui.h"
#include "NrScript/platform/linux/NrWindowImplOSUnix.h"
#include "NrScript/skia.h"

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
        if (m_widget == nullptr) {
            return false;
        }

        ::gtk_window_set_title(GTK_WINDOW(m_widget), "");
        ::gtk_window_resize(GTK_WINDOW(m_widget), parameter.bounds.width, parameter.bounds.height);
        ::gtk_window_move(GTK_WINDOW(m_widget), parameter.bounds.x, parameter.bounds.y);

        /**
         * 创建GTK窗口对象之后，需要设定事件
         */
        return m_pOwner->initialEvents();
    }

    NrWindowBase* getNativeWindow() override {
        return m_pOwner;
    }

    bool isActive() const override {
        return false;
    }

    void show() override {
        ::gtk_widget_show(m_widget);
    }

    void showInactive() override {

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

    void setContentView(NrControl* root) override {
        m_renderer->setRenderTarget(root);
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

NrWindowBase* NrWindowImplOSUnix::getNativeWindow() {
    return impl->getNativeWindow();
}

bool NrWindowImplOSUnix::isActive() const {
    return impl->isActive();
}

void NrWindowImplOSUnix::show() {
    return impl->show();
}

void NrWindowImplOSUnix::showInactive() {
    return impl->showInactive();
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
	 * gtk的MW_ONCREATE消息是哪个？ 有知道的请告诉我
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