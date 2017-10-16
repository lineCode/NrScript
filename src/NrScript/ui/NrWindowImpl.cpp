#include "NrScript/base.h"
#include "NrScript/ui.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include "NrScript/platform/linux/NrWindowImplOSUnix.h"
#else
#include "NrScript/platform/windows/NrWindowImplOSWin.h"
#endif

static void kNotifyTraversals(NrWindowBase* sender, const NrRect& bounds) {
    NrWindowImpl* impl = dynamic_cast<NrWindowImpl*>(sender);
    if (impl == nullptr) {
        return;
    }
}

/**
 * NrWindowImpl
 */

NrWindowImpl::NrWindowImpl() {
#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
    impl = new NrWindowImplOSUnix(this);
#else
    impl = new NrWindowImplOSWin(this);
#endif

    /**
     * 对象初始化
     */
    this->m_render = new NrWidgetsTreeRenderer();

    /**
     * 事件设置
     */
    this->eOnSizePtr->add(kNotifyTraversals);
}

NrWindowImpl::~NrWindowImpl() {
    delete impl;
}

bool NrWindowImpl::create(const NrWindowCreateParameter& parameter) {
    return impl->create(parameter);
}

NrWindowBase* NrWindowImpl::getNativeWindow() {
    return impl->getNativeWindow();
}

bool NrWindowImpl::isActive() const {
    return impl->isActive();
}

void NrWindowImpl::show() {
    return impl->show();
}

void NrWindowImpl::showInactive() {
    return impl->showInactive();
}

void NrWindowImpl::setBounds(const NrRect& bounds) {
    return impl->setBounds(bounds);
}

NrRect NrWindowImpl::getBounds() const {
    return impl->getBounds();
}

void NrWindowImpl::setRootControl(NrControl* root) {
    /**
     * 通用代码，不需要区分platform实现
     */
    if (root != nullptr) {
        m_root = root;

        /**
         * 还是不对啊。
         */
        NrRect bounds = getBounds();
        m_render->doTraversal(m_root, bounds.width, bounds.height);
    }
}