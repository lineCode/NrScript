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
    typedef typename std::remove_reference<T>::type value_type;

public:
    /**
     * 获取属性值
     */
    operator value_type() {
        return m_value;
    }

    /**
     * 赋值
     */
    NrWidgetProperty<T>& operator = (const NrWidgetProperty<T>& value) {
        m_value = value.m_value;
        return *this;
    }

    /**
     * 赋值
     */
    NrWidgetProperty<T>& operator = (const value_type& value) {
        m_value = value;
        return *this;
    }

    /**
     * 从字符串中解析所需要的数据
     */
    NrWidgetProperty<T>& acceptString(const NrString& source) {
        source;
        return *this;
    }

    /**
     * 转为字符串
     */
    //NrString& toString() {
    //    return NrString();
    //}

private:
    /**
     * 属性值
     */
    value_type m_value {};
};

#endif
