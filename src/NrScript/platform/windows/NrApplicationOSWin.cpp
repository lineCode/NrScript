/**
 * NrScript Source Code File saved as UTF-8.bom format */

#include "NrScript/base.h"
#include "NrScript/platform/windows/NrApplicationOSWin.h"

int NrApplicationOSWin::exit(int exitCode) {
    PostQuitMessage(exitCode);
    return exitCode;
}