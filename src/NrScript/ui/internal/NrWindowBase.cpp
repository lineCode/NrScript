#include "NrScript/base.h"
#include "NrScript/ui.h"

NrWindowBase::CommonEvents::CommonEvents() {
    eOnCreatePtr = new NrEvent<void(NrWindowBase*, NrReserved)>();
    eOnClosePtr = new NrEvent<void(NrWindowBase*, bool&)>();
    eOnDestroyPtr = new NrEvent<void(NrWindowBase*, NrReserved)>();
}

NrWindowBase::CommonEvents::~CommonEvents() {
    delete eOnCreatePtr;
    delete eOnClosePtr;
    delete eOnDestroyPtr;
}