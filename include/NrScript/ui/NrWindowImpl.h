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
     * 获取与平台相关的系统本地窗口
     */
    virtual NrWindowBase* getNativeWindow() override;

    /**
     * 确认当前窗口状态是否ACTIVE
     */
    virtual bool isActive() const override;

    /**
     * 当前窗口是否显示
     */
    virtual bool isVisible() const override;

    /**
     * 显示窗口
     */
    virtual void show() override;

    /**
     * 作为指定窗口的子窗口显示
     */
    virtual void show(NrWindowBase* parent) override;

    /**
     * 作为模态窗口显示，使用场景为对话框，但对话框处理结果(返回值)需要自己设置
     * @param [in] parent 父窗口
     */
    virtual void showModal(NrWindowBase* parent) override;

    /**
     * 显示窗口但不激活
     */
    virtual void showInactive() override;

    /**
     * 设置窗口位置、客户区大小
     */
    virtual void setBounds(const NrRect& bounds) override;

    /**
     * 获取窗口位置、客户区大小
     */
    virtual NrRect getBounds() const override;

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
