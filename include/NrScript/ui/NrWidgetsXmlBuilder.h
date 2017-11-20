/**
* NrScript Source Code File saved as UTF-8.bom format
*
* note : 1. NrScript��������char�����ַ���(���֡�����)�����޶�ΪӢ��
*        2. ���ض�ϵͳƽ̨��صĴ��룬�����platformĿ¼��
*
*
*
*
*
*
*
*
* !��Ҫ�ڴ�����ƽ̨��ص�ͷ�ļ���
*/

#ifndef _NOSCRIPT_NRWIDGETSBUILDER_H_
#define _NOSCRIPT_NRWIDGETSBUILDER_H_

template class NRSCRIPT_API_VISUAL NrEvent<void(const NrString&, NrControl& retval)>;

/**
 * ����xml�Զ������ؼ�����
 */
class NRSCRIPT_API_VISUAL NrWidgetsXmlBuilder {
public:
    /**
     * ͨ�����������ؼ�����
     */
    class NRSCRIPT_API_VISUAL NrWidgetStringCreatorBase {
    public:
        /**
         * Ĭ����������
         */
        virtual ~NrWidgetStringCreatorBase() {};

        /**
         * �����ؼ�
         */
        virtual NrControl* create() = 0;
    };

public:
    /**
     * Ĭ�Ϲ��캯��
     */
    NrWidgetsXmlBuilder();
    
    /**
     * ��������
     */
    virtual ~NrWidgetsXmlBuilder();

public:
    /**
     * ע��ؼ�
     * @param widgetClassName   �ؼ�����
     * @param creator           �ؼ�������
     * @return �Ƿ�ע��ɹ�
     * 
     * @note ע��Ŀؼ��࣬������Ĭ�Ϲ��캯�������û��Ĭ�Ϲ��캯�����޷�����.
     *       �޷�ע��Ŀؼ���Ҫͨ��xml�������Զ����������Թ�עeOnCreateWidget�¼���ʵ��
     */
    bool registerWidget(const NrString& widgetClassName, NrWidgetStringCreatorBase* creator);

public:
    /**
     * �����ؼ��¼�
     * @param NrString      �ؼ�����
     * @param retval        �����Ŀؼ�
     */
    NrEvent<void(const NrString&, NrControl& retval)> eOnCreateWidget;

    /**
     * 
     */
    std::map<NrString, NrWidgetStringCreatorBase*>* m_creators;
};

#endif
