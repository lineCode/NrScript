﻿/**
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

#ifndef _NRSCRIPT_WINDOWIMPL_H_
#define _NRSCRIPT_WINDOWIMPL_H_ 1

/**
 * WM_NCACTIVATE = 对话框闪烁。
 */
class NRSCRIPT_API_VISUAL NrWindowImpl : public NrWindowBase,
                                         public NrWindowBase::CommonEvents {
public:
    /**
     * 默认构造函数
     */
    NrWindowImpl();

    /**
     * 虚拟析构函数
     */
    virtual ~NrWindowImpl();

public:
    /**
     * 创建窗口
     */
    virtual bool create(const NrWindowBase::CreateParameter& parameter) override;

    /**
     * 关闭窗口
     */
    virtual void close() override;

    /**
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() const override;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const override;

    /**
     * 当前窗口是否显示
     */
    virtual bool isVisible() const override;

    /**
     * 是否模态对话框形式
     */
    virtual bool isDialog() const override;

    /**
     * 显示窗口
     */
    virtual void show() override;

    /**
     * 作为指定窗口的子窗口显示
     */
    virtual void show(NrWindowBase* parent) override;

    /**
     * 作为模态对话框显示
     * @param parent 父窗口
     * @remarks 作为模态对话框的情况下，点击关闭按钮或者调用close，并不会真正的关闭
     * 窗口(DestroyWindow)，而是隐藏。
     */
    virtual NrDialogResult showDialog(NrWindowBase* parent) override;

    /**
     * 设置对话框返回值
     * @remarks 此函数将终止模态对话框显示
     */
    virtual void setDialogResult(const NrDialogResult result) override;

    /**
     * 显示窗口但不激活
     */
    virtual void showInactive() override;

    /**
     * 隐藏窗口
     */
    virtual void hide() override;

    /**
     * 设置窗口位置、客户区大小
     */
    virtual void setBounds(const NrRect& bounds) override;

    /**
     * 获取窗口位置、客户区大小
     */
    virtual NrRect getBounds() const override;

    /**
     * 屏幕居中
     */
    virtual void centerScreen() override;

    /**
     * 父窗口居中
     */
    virtual void centerWindow(const NrWindowBase* parent) override;

public:
    /**
     * 设置渲染树
     */
    virtual void setContentView(NrControl* root) override;

private:
    /**
     * 桥接
     */
    NrWindowBase* impl {nullptr};
};

#endif
