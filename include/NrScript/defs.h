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
    
    /**
     * 如果模板编译以及在其他工程中引用出现"4251"警告，则使用 NRSCRIPT_TEMPLATE_VISUAL解决
     */
    #ifdef NRSCRIPT_TEMPLATE_EXPORT
        #define NRSCRIPT_TEMPLATE_VISUAL    __attribute__((visibility("default")))
    #else
        #define NRSCRIPT_TEMPLATE_VISUAL    
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
