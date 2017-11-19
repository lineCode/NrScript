#ifndef _NOSCRIPT_NRWIDGETSBUILDER_H_
#define _NOSCRIPT_NRWIDGETSBUILDER_H_

/**
 * 创建类
 */
class NRSCRIPT_API_VISUAL NrWidgetStringCreatorBase {
public:
    /**
     * 默认构造函数
     */
    virtual ~NrWidgetStringCreatorBase() = default;

public:
    /**
     * 控件创建
     */
    virtual NrControl* create() = 0;

    /**
     * 释放内存
     */
    virtual void destroy() = 0;
};

template class NRSCRIPT_API_VISUAL NrEvent<NrControl*(const NrString&, NrControl*&)>;

/**
 * 读取xml文件自动创建控件工具
 */
class NRSCRIPT_API_VISUAL NrWidgetsXmlBuilder {
private:
    /**
     * 默认构造函数
     */
    NrWidgetsXmlBuilder();

    /**
     * 析构函数
     */
    ~NrWidgetsXmlBuilder();

public:
    /**
     * 单例
     */
    static NrWidgetsXmlBuilder& instance();

public:
    /**
     * 注册控件
     */
    void registerWidget(const NrString& widgetClassName, NrWidgetStringCreatorBase* creator);

    /**
     * 创建控件
     */
    NrControl* ceateWidget(const NrString& name);

private:
    /**
     * 控件创建管理
     */
    std::map<NrString, NrWidgetStringCreatorBase*> m_creators;

public:
    /**
     * 创建控件时触发
     *
     * @param [in] NrString&    正在创建的控件的名称
     * @param [in] NrControl*   已经创建的控件，可能是nullptr。如果是nullptr，则
     *                          可能是未注册的控件，需要你手动创建。
     */
    NrEvent<NrControl*(const NrString&, NrControl*&)> eOnCreateWidget;
};

/**
 * 用于预注册控件
 */
template<typename WIDGET>
class NrWidgetStringCreator : public NrWidgetStringCreatorBase {
public:
    /**
     * 默认构造函数
     */
    NrWidgetStringCreator(const wchar_t* widgetClassName) {
        NrWidgetsXmlBuilder::instance().registerWidget(widgetClassName, new NrWidgetStringCreator<WIDGET>());
    }

    /**
     * 默认析构函数
     */
    ~NrWidgetStringCreator() {
    }

private:
    /**
     * 仅供NrXmlWidgetBuilder使用
     */
    NrWidgetStringCreator() {
        
    }

public:
    /**
     * 创建控件
     * 控件必须有默认构造函数，如果没有的话无法注册，可以在NrWidgetsXmlBuilder::eOnCreateWidgets事件中手动创建
     */
    NrControl* create() override {
        return dynamic_cast<NrControl*>(new WIDGET());
    }

    void destroy() override {
        delete this;
    }
};

#endif
