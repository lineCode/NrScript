#ifndef _NRSCRIPTBUILDER_NRBUILDERFRAME_H_
#define _NRSCRIPTBUILDER_NRBUILDERFRAME_H_ 1

#include <NrScript.h>

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
#include <Windows.h>
#endif

/**
 * NrScript.Builder 主窗口
 */
class NrBuilderFrame : public NrDialogImpl {
public:
    /**
     * 默认构造函数
     */
    NrBuilderFrame();
    
    /**
     * 析构函数
     */
    ~NrBuilderFrame();

public:

private:
    /**
     * 窗口创建消息
     */
    void OnFrameCreate(NrWindowBase* sender, NrReserved reserved);

    /**
     * 窗口关闭事件
     */
    void OnClose(NrWindowBase* sender, bool& closeable);

    /**
     * 窗口销毁通
     */
    void OnFrameDestroy(NrWindowBase* sender, NrReserved reserved);
};

#endif
