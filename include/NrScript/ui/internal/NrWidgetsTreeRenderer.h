/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : 1. NrScript库中所有char常量字符串(文字、符号)必须限定为英文 
 *        2. 与特定系统平台相关的代码，请放入platform目录中
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 * !不要在此引入平台相关的头文件，
 */

#ifndef _NRSCRIPT_NRCONTROLRENDERMANAGER_H_
#define _NRSCRIPT_NRCONTROLRENDERMANAGER_H_ 1

/**
 * 控件渲染管理
 */
class NRSCRIPT_API_VISUAL NrWidgetsTreeRenderer {
public:
    /**
     * 默认构造函数
     */
    NrWidgetsTreeRenderer();
    
    /**
     * 析构函数
     */
    virtual ~NrWidgetsTreeRenderer();

public:
    /**
     * 设置渲染根节点
     */
    void setRenderTarget(NrControl* root);

    /**
     * 设置根节点，重新绘制
     */
    void doTraversal(int width, int height);

private:
    /**
     * 根节点控件
     */
    NrControl* m_root {nullptr};

    /**
     * 目标窗体客户区宽度
     */
    int m_hostWidth {0};

    /**
     * 目标窗体客户区高度
     */
    int m_hostHeight {0};
};

#endif
