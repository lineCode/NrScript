#ifndef _NRSCRIPT_NRAPPLICATIONOSUNIX_H_
#define _NRSCRIPT_NRAPPLICATIONOSUNIX_H_ 1

#include <gtk/gtk.h>

/**
 * 应用程序类
 */
class NRSCRIPT_API_VISUAL NrApplicationOSUnix {
public:
    /**
     * 退出程序
     */
    static int exit(int exitCode);
};

#endif
