#ifndef _NRSCRIPT_NRDIALOGIMPL_H_
#define _NRSCRIPT_NRDIALOGIMPL_H_ 1

/**
 * 对话框窗口
 */
class NRSCRIPT_API_VISUAL NrDialogImpl : public NrWindowImpl {
private:
    /**
     * 创建窗口
     */
    bool create(const NrWindowCreateParameter& parameter) override;
};

#endif
