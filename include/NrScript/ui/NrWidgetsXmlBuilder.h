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

#ifndef _NOSCRIPT_NRWIDGETSBUILDER_H_
#define _NOSCRIPT_NRWIDGETSBUILDER_H_

template class NRSCRIPT_API_VISUAL NrEvent<void(const NrString&, NrControl& retval)>;

/**
 * 解析xml自动创建控件工具
 */
class NRSCRIPT_API_VISUAL NrWidgetsXmlBuilder {
public:
    /**
     * 通过类名创建控件对象
     */
    class NRSCRIPT_API_VISUAL NrWidgetStringCreatorBase {
    public:
        /**
         * 默认析构函数
         */
        virtual ~NrWidgetStringCreatorBase() {};

        /**
         * 创建控件
         */
        virtual NrControl* create() = 0;
    };

public:
    /**
     * 默认构造函数
     */
    NrWidgetsXmlBuilder();
    
    /**
     * 析构函数
     */
    virtual ~NrWidgetsXmlBuilder();

public:
    /**
     * 注册控件
     * @param widgetClassName   控件类名
     * @param creator           控件创建类
     * @return 是否注册成功
     * 
     * @note 注册的控件类，必须有默认构造函数，如果没有默认构造函数则无法创建.
     *       无法注册的控件想要通过xml构建器自动创建，可以关注eOnCreateWidget事件来实现
     */
    bool registerWidget(const NrString& widgetClassName, NrWidgetStringCreatorBase* creator);

public:
    /**
     * 创建控件事件
     * @param NrString      控件名称
     * @param retval        创建的控件
     */
    NrEvent<void(const NrString&, NrControl& retval)> eOnCreateWidget;

    /**
     * 
     */
    std::map<NrString, NrWidgetStringCreatorBase*>* m_creators;
};

#endif
