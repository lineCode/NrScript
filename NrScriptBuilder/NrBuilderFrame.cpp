#include "NrBuilderFrame.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include <gtk/gtk.h>
#endif

void ddd(NrWindowBase* sender, NrReserved reserved) {
    printf("\n AAAAAAAAAAAAAA");
}

NrBuilderFrame::NrBuilderFrame() {
    this->eOnCreatePtr->add(this, &NrBuilderFrame::OnFrameCreate);
    this->eOnDestroyPtr->add(this, &NrBuilderFrame::OnFrameDestroy);
    this->eOnClosePtr->add(this, &NrBuilderFrame::OnClose);
    this->eOnDestroyPtr->add(ddd);
}

NrBuilderFrame::~NrBuilderFrame() {
    
}

void NrBuilderFrame::OnFrameCreate(NrWindowBase* sender, NrReserved reserved) {
    
}

void NrBuilderFrame::OnClose(NrWindowBase* sender, bool& closeable) {
    closeable = true;

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    ::PostQuitMessage(0);
#else
    ::gtk_main_quit();
#endif
}

void NrBuilderFrame::OnFrameDestroy(NrWindowBase* sender, NrReserved reserved) {
    printf("\ndestroyed");
}