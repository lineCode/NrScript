/**
 * NrScript Source Code File saved as UTF-8.bom format */

#ifndef _NRSCRIPT_DEFS_H_
#define _NRSCRIPT_DEFS_H_ 1

/**
 * 不要在此引入平台相关的头文件
 */

#include <string>
#include <vector>
#include <cassert>

using NrReserved = int;

#define NRSCRIPT_UNREFERENCED_PARAMETER(x) (x)

#ifdef NRSCRIPT_BUILD_PLATFORM_LINUX
    #ifdef NRSCRIPT_EXPORTS
        #define NRSCRIPT_API_VISUAL         __attribute__((visibility("default")))
        #define NRSCRIPT_API_HIDDEN         __attribute__((visibility("hidden")))
    #else
        #define NRSCRIPT_API_VISUAL
        #define NRSCRIPT_API_HIDDEN
    #endif

    #ifdef DEBUG
        #define NRSCRIPT_ASSERT(x)     {assert((x));}
        #define NRSCRIPT_DEBUG   1
    #else
        #define NRSCRIPT_ASSERT(x)
        #define NRSCRIPT_DEBUG   0
    #endif
#else
    #ifdef NRSCRIPT_EXPORTS
        #define NRSCRIPT_API_VISUAL         __declspec(dllexport)
        #define NRSCRIPT_API_HIDDEN
    #else
        #define NRSCRIPT_API_VISUAL         __declspec(dllimport)
        #define NRSCRIPT_API_HIDDEN
    #endif

    #ifdef _DEBUG
        #define NRSCRIPT_ASSERT(x)     {assert((x));}
        #define NRSCRIPT_DEBUG   1
    #else
        #define NRSCRIPT_ASSERT(x)
        #define NRSCRIPT_DEBUG   0
    #endif
#endif

#endif
