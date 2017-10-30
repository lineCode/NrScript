#include "NrScript/base.h"
#include "NrScript/ui.h"

bool NrDialogImpl::create(const NrWindowBase::CreateParameter& parameter) {
    NRSCRIPT_UNREFERENCED_PARAMETER(parameter);
    return NrWindowImpl::create(parameter);
}

void NrDialogImpl::show() {
    return NrWindowImpl::show();
}

int NrDialogImpl::showModal() {
    return 0;
}