#include "NrScript/base.h"
#include "NrScript/platform/windows/NrApplicationOSWin.h"

int NrApplicationOSWin::exit(int exitCode) {
    PostQuitMessage(exitCode);
    return exitCode;
}