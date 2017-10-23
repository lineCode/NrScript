#ifndef _NRSCRIPT_NRWIDGETPROPERTY_H_
#define _NRSCRIPT_NRWIDGETPROPERTY_H_ 1

/**
 * 控件属性辅助工具
 */
template<typename T>
class NrWidgetProperty {
public:
    /**
     * 属性值类型
     */
    typedef typename std::remove_reference<T>::type property_type;

public:
    /**
     * 获取属性值
     */
    operator property_type() {
        return m_value;
    }

private:
    /**
     * 属性值
     */
    property_type m_value {};
};

#endif
