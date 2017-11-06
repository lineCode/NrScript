#ifndef _NRSCRIPTBUILDER_NRBUILDERFRAME_H_
#define _NRSCRIPTBUILDER_NRBUILDERFRAME_H_ 1

#include <NrScript.h>
#include "NrAboutDialog.h"
#include <memory>

/**
 * NrScript.Builder 主窗口
 */
class NrBuilderFrame : public NrWindowImpl {
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
    void OnFrameClose(NrWindowBase* sender, bool& closeable);

    /**
     * 窗口销毁通
     */
    void OnFrameDestroy(NrWindowBase* sender, NrReserved reserved);

private:
    /**
     * 关于对话框
     */
    std::unique_ptr<NrAboutDialog> m_dlgAbout{new NrAboutDialog};
};

#endif
