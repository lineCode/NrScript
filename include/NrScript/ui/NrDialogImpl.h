#ifndef _NRSCRIPT_NRDIALOGIMPL_H_
#define _NRSCRIPT_NRDIALOGIMPL_H_ 1

/**
 * 对话框窗口
 */
class NRSCRIPT_API_VISUAL NrDialogImpl : public NrWindowImpl, 
                                         public NrDialogBase {
public:
    /**
    * 创建窗口
    */
    virtual bool create(const NrWindowBase::CreateParameter& parameter) override;
    
    /**
     * 显示非模态对话框
     */
    virtual void show() override;

    /**
     * 显示模态对话框
     */
    virtual int showModal() override;
};

#endif
