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
 * !不要在此引入平台相关的头文件，
 */

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

void NrWindowImpl::close() {
    return impl->close();
}

NrWindowBase* NrWindowImpl::getNativeWindow() const {
    return impl->getNativeWindow();
}

bool NrWindowImpl::isActive() const {
    return impl->isActive();
}

bool NrWindowImpl::isVisible() const {
    return impl->isVisible();
}

bool NrWindowImpl::isDialog() const {
    return impl->isDialog();
}

void NrWindowImpl::show() {
    return impl->show();
}

void NrWindowImpl::show(NrWindowBase* parent) {
    return impl->show(parent);
}

NrDialogResult NrWindowImpl::showDialog(NrWindowBase* parent) {
    return impl->showDialog(parent);
}

void NrWindowImpl::setDialogResult(const NrDialogResult result) {
    return impl->setDialogResult(result);
}

void NrWindowImpl::showInactive() {
    return impl->showInactive();
}

void NrWindowImpl::hide() {
    return impl->hide();
}

void NrWindowImpl::setBounds(const NrRect& bounds) {
    return impl->setBounds(bounds);
}

NrRect NrWindowImpl::getBounds() const {
    return impl->getBounds();
}

void NrWindowImpl::centerScreen() {
    return impl->centerScreen();
}

void NrWindowImpl::centerParent(const NrWindowBase* parent) {
    return impl->centerParent(parent);
}

void NrWindowImpl::setContentView(NrControl* root) {
    return impl->setContentView(root);
}