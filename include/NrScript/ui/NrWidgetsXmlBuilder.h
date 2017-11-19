#ifndef _NOSCRIPT_NRWIDGETSBUILDER_H_
#define _NOSCRIPT_NRWIDGETSBUILDER_H_

/**
 * ������
 */
class NRSCRIPT_API_VISUAL NrWidgetStringCreatorBase {
public:
    /**
     * Ĭ�Ϲ��캯��
     */
    virtual ~NrWidgetStringCreatorBase() = default;

public:
    /**
     * �ؼ�����
     */
    virtual NrControl* create() = 0;

    /**
     * �ͷ��ڴ�
     */
    virtual void destroy() = 0;
};

template class NRSCRIPT_API_VISUAL NrEvent<NrControl*(const NrString&, NrControl*&)>;

/**
 * ��ȡxml�ļ��Զ������ؼ�����
 */
class NRSCRIPT_API_VISUAL NrWidgetsXmlBuilder {
private:
    /**
     * Ĭ�Ϲ��캯��
     */
    NrWidgetsXmlBuilder();

    /**
     * ��������
     */
    ~NrWidgetsXmlBuilder();

public:
    /**
     * ����
     */
    static NrWidgetsXmlBuilder& instance();

public:
    /**
     * ע��ؼ�
     */
    void registerWidget(const NrString& widgetClassName, NrWidgetStringCreatorBase* creator);

    /**
     * �����ؼ�
     */
    NrControl* ceateWidget(const NrString& name);

private:
    /**
     * �ؼ���������
     */
    std::map<NrString, NrWidgetStringCreatorBase*> m_creators;

public:
    /**
     * �����ؼ�ʱ����
     *
     * @param [in] NrString&    ���ڴ����Ŀؼ�������
     * @param [in] NrControl*   �Ѿ������Ŀؼ���������nullptr�������nullptr����
     *                          ������δע��Ŀؼ�����Ҫ���ֶ�������
     */
    NrEvent<NrControl*(const NrString&, NrControl*&)> eOnCreateWidget;
};

/**
 * ����Ԥע��ؼ�
 */
template<typename WIDGET>
class NrWidgetStringCreator : public NrWidgetStringCreatorBase {
public:
    /**
     * Ĭ�Ϲ��캯��
     */
    NrWidgetStringCreator(const wchar_t* widgetClassName) {
        NrWidgetsXmlBuilder::instance().registerWidget(widgetClassName, new NrWidgetStringCreator<WIDGET>());
    }

    /**
     * Ĭ����������
     */
    ~NrWidgetStringCreator() {
    }

private:
    /**
     * ����NrXmlWidgetBuilderʹ��
     */
    NrWidgetStringCreator() {
        
    }

public:
    /**
     * �����ؼ�
     * �ؼ�������Ĭ�Ϲ��캯�������û�еĻ��޷�ע�ᣬ������NrWidgetsXmlBuilder::eOnCreateWidgets�¼����ֶ�����
     */
    NrControl* create() override {
        return dynamic_cast<NrControl*>(new WIDGET());
    }

    void destroy() override {
        delete this;
    }
};

#endif
