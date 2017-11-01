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
        closeable = false;
        NrDialogResult result = m_dlgAbout->showDialog(sender);
        if (result != NrDialogResult::Exception) {
            closeable = false;
        }
    } else if (sender == m_dlgAbout.get()) {
        sender->setDialogResult(NrDialogResult::Cancel);
    }

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    if (closeable && sender == this) {
        ::PostQuitMessage(0);
    }
#else
    ::gtk_main_quit();
#endif
}

void NrBuilderFrame::OnFrameDestroy(NrWindowBase* sender, NrReserved reserved) {
    printf("\ndestroyed");
}