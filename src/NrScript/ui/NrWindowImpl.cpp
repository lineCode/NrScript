#include "NrScript/base.h"
#include "NrScript/ui.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include "NrScript/platform/linux/NrWindowImplOSUnix.h"
#else
#include "NrScript/platform/windows/NrWindowImplOSWin.h"
#endif

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
        NrRect bounds = getBounds();
        m_render->doTraversal(bounds.width, bounds.height);
    }
}

void NrWindowImpl::norityTraversalsRender(const int width, const int height) {
    m_render->doTraversal(width, height);
}