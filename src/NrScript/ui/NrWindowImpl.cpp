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
}

NrWindowImpl::~NrWindowImpl() {
    delete impl;
}

bool NrWindowImpl::create(const NrWindowBase::CreateParameter& parameter) {
    return impl->create(parameter);
}

NrWindowBase* NrWindowImpl::getNativeWindow() {
    return impl->getNativeWindow();
}

bool NrWindowImpl::isActive() const {
    return impl->isActive();
}

bool NrWindowImpl::isVisible() const {
    return impl->isVisible();
}

void NrWindowImpl::show() {
    return impl->show();
}

void NrWindowImpl::show(NrWindowBase* parent) {
    return impl->show(parent);
}

void NrWindowImpl::showModal(NrWindowBase* parent) {
    return impl->showModal(parent);
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

void NrWindowImpl::setContentView(NrControl* root) {
    impl->setContentView(root);
}