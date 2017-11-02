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
    this->eOnClose.add(this, &NrBuilderFrame::OnFrameClose);
    this->eOnDestroy.add(ddd);

    this->m_dlgAbout->eOnClose.add(this, &NrBuilderFrame::OnFrameClose);
}

NrBuilderFrame::~NrBuilderFrame() {
    
}

void NrBuilderFrame::OnFrameCreate(NrWindowBase* sender, NrReserved reserved) {
    NrWindowBase::CreateParameter p{};
    p.bounds.width = 480;
    p.bounds.height = 272;
    m_dlgAbout->create(p);
}

void NrBuilderFrame::OnFrameClose(NrWindowBase* sender, bool& closeable) {
    if (sender == this) {
        m_dlgAbout->showDialog(this);
    }
    else if (sender == m_dlgAbout.get()) {
        closeable = true;
    }

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    if (closeable && sender == this) {
        ::PostQuitMessage(0);
    }
#else
    //::gtk_main_quit();
#endif
}

void NrBuilderFrame::OnFrameDestroy(NrWindowBase* sender, NrReserved reserved) {
    printf("\ndestroyed");
}