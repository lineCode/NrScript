#ifndef _NRSCRIPTBUILDER_NRBUILDERAPP_H_
#define _NRSCRIPTBUILDER_NRBUILDERAPP_H_ 1

#include <memory>
#include "NrBuilderFrame.h"

class NrBuilderApp {
public:
    /**
     * 默认构造函数
     */
    NrBuilderApp();
    
    /**
     * 析构函数
     */
    ~NrBuilderApp();

public:
    /**
     * 初始化
     */
    bool initialize();

private:
    /**
     * 程序主窗口
     */
    std::shared_ptr<NrBuilderFrame> m_builderFrame {new NrBuilderFrame};
};

#endif
