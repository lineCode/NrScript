/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : NrScript库中所有常量字符串(文字、符号)必须限定为英文 
 */

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