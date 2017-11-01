#include "NrBuilderFrame.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include <gtk/gtk.h>
#endif

void ddd(NrWindowBase* sender, NrReserved reserved) {
    printf("\n AAAAAAAAAAAAAA");
}

NrBuilderFrame::NrBuilderFrame() {
    this->eOnCreate.add(this, &NrBuilderFrame::OnFrameCreate);
    this->eOnDestroy.add(this, &NrBuilderFrame::OnFrameDestroy);
    this->eOnClose.add(this, &NrBuilderFrame::OnClose);
    this->eOnDestroy.add(ddd);
}

NrBuilderFrame::~NrBuilderFrame() {
    
}

void NrBuilderFrame::OnFrameCreate(NrWindowBase* sender, NrReserved reserved) {
    NrWindowBase::CreateParameter p{};
    p.bounds.width = 480;
    p.bounds.height = 272;
    m_dlgAbout->create(p);
}

void NrBuilderFrame::OnClose(NrWindowBase* sender, bool& closeable) {
    closeable = false;

    m_dlgAbout->showModal(this);

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    if (closeable) {
        ::PostQuitMessage(0);
    }
#else
    ::gtk_main_quit();
#endif
}

void NrBuilderFrame::OnFrameDestroy(NrWindowBase* sender, NrReserved reserved) {
    printf("\ndestroyed");
}