/**
 * NrScript Source Code File saved as UTF-8.bom format */
 
#include "NrScript/base.h"
#include "NrScript/platform/linux/NrApplicationOSUnix.h"

int NrApplicationOSUnix::exit(int exitCode) {
    ::gtk_main_quit();
    return exitCode;
}