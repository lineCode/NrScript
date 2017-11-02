#include "NrScript/base.h"
#include "NrScript/ui/NrApplication.h"

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
#include "NrScript/platform/linux/NrApplicationOSUnix.h"
#else
#include "NrScript/platform/windows/NrApplicationOSWin.h"
#endif

int NrApplication::exit(int exitCode) {
#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
    return NrApplicationOSUnix::exit(exitCode);
#else
    return NrApplicationOSWin::exit(exitCode);
#endif
}