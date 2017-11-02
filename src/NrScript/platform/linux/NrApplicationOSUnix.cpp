#include "NrScript/base.h"
#include "NrScript/platform/linux/NrApplicationOSUnix.h"

int NrApplicationOSUnix::exit(int exitCode) {
    ::gtk_main_quit();
    return exitCode;
}