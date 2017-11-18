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

#ifndef _NRSCRIPT_EVENT_H_
#define _NRSCRIPT_EVENT_H_ 1

/**
 * 基础事件定义：有且只有2个参数，返回值类型不限定。非线程安全函数！
 *
 * @author rHongCN 9.24.2017
 *
 * 可绑定成员函数、非成员函数。
 */

template<typename signature>
class NrEvent;

/**
 * 不推荐使用NrEvent代理虚函数。如果子类重载父类虚函数，同时也将子类虚函数
 * add到事件列表中，那...
 */
template<typename RETVAL_T, typename SENDER_T, typename PARAM_T>
class NrEvent<RETVAL_T(SENDER_T, PARAM_T)> {
public:
    typedef RETVAL_T retval_type;
    typedef SENDER_T sender_type;
    typedef PARAM_T  parameter_type;

private:
    /**
     * 适配器
     */
    template<typename signature>
    class NrEventAdapter;
    
    /**
     * 适配器 偏特化：普通函数
     */
    template<typename RETVAL_U, typename SENDER_U, typename PARAM_U>
    class NrEventAdapter<RETVAL_U(SENDER_U, PARAM_U)> {
    public:
        typedef RETVAL_U(*Callback)(SENDER_U, PARAM_U);
    };

    /**
     * 适配器 偏特化：成员函数
     */
    template<typename RETVAL_U, typename SENDER_U, typename PARAM_U, typename CLASS_U>
    class NrEventAdapter<RETVAL_U(CLASS_U::*)(SENDER_U, PARAM_U)> {
    public:
        typedef CLASS_U class_type;

    public:
        typedef RETVAL_U(CLASS_U::*Callback)(SENDER_U, PARAM_U);
    };

private:
    /**
     * 函数指针基类
     */
    class NrEventCallback {
    public:
        /**
         * 虚拟析构函数
         */
        virtual ~NrEventCallback() {};

        /**
         * 调用函数指针
         */
        virtual retval_type run(sender_type, parameter_type) = 0;

        /**
         * 确认函数指针内容是否一致
         */
        virtual bool isEquals(const NrEventCallback* callback) = 0;

        /**
         * 新实例
         */
        virtual NrEventCallback* newInstance() const = 0;

        /**
         * 清除函数指针内容
         */
        virtual void reset() = 0;
        
        /**
         * 确认函数指针是否可用
         */
        virtual bool isEnable() = 0;
    };

    /**
     * 成员函数指针
     */
    template<typename T>
    class NrEventCallbackComplex : public NrEventCallback {
    public:
        retval_type run(sender_type sender, parameter_type parameter) override {
        #ifdef NRSCRIPT_DEBUG
            if (m_object == nullptr || m_callback == nullptr) {
                NRSCRIPT_ASSERT(false);
            }
        #endif
            return (m_object->*m_callback)(sender, parameter);
        }

        bool isEquals(const NrEventCallback* callback) override {
            const NrEventCallbackComplex<T>* pComplex = dynamic_cast<const NrEventCallbackComplex<T>*>(callback);
            if (pComplex && pComplex->m_object == m_object && pComplex->m_callback == m_callback) {
                return true;
            }
            return false;
        }

        NrEventCallback* newInstance() const override {
            NrEventCallbackComplex<T>* retval = new NrEventCallbackComplex<T>();
            retval->m_object = m_object;
            retval->m_callback = m_callback;

            return retval;
        }

        void reset() override {
            m_object = nullptr;
            m_callback = nullptr;
        }

        bool isEnable() override {
            return (m_object != nullptr && m_callback != nullptr);
        }

    public:
        T* m_object {nullptr};
        typename NrEventAdapter<retval_type(T::*)(sender_type, parameter_type)>::Callback m_callback {nullptr};
    };

    /**
     * 普通函数指针
     */
    class NrEventCallbackSimple : public NrEventCallback {
    public:
        retval_type run(sender_type sender, parameter_type parameter) override {
        #ifdef NRSCRIPT_DEBUG
            if (m_callback == nullptr) {
                NRSCRIPT_ASSERT(false);
            }
        #endif
            return m_callback(sender, parameter);
        }

        bool isEquals(const NrEventCallback* callback) override {
            const NrEventCallbackSimple* pSimple = dynamic_cast<const NrEventCallbackSimple*>(callback);
            if (pSimple && pSimple->m_callback == m_callback) {
                return true;
            }
            return false;
        }

        NrEventCallback* newInstance() const override {
            NrEventCallbackSimple* retval = new NrEventCallbackSimple();
            retval->m_callback = m_callback;

            return retval;
        }

        void reset() override {
            m_callback = nullptr;
        }

        bool isEnable() override {
            return (m_callback != nullptr);
        }

    public:
        typename NrEventAdapter<retval_type(sender_type, parameter_type)>::Callback m_callback {nullptr};
    };

    /**
     * 函数指针管理
     */
    class NrEventCallbackList {
    public:
        /**
         * 默认构造、析构
         */
        NrEventCallbackList() {
            m_vector = new std::vector<NrEventCallback *>();
        }

        ~NrEventCallbackList() {
            for (auto i = m_vector->begin() ; i != m_vector->end() ; ) {
                NrEventCallback* cb = (*i);
                i = m_vector->erase(i);
                delete cb;
            }
            delete m_vector;
        }
    public:
        bool add(const NrEventCallback& callback) {
            if (!contains(callback)) {
                m_vector->push_back(callback.newInstance());
            }
            return contains(callback);
        }

        bool remove(const NrEventCallback& callback) {
            for (auto i = m_vector->begin() ; i != m_vector->end() ; i++) {
                if ((*i)->isEquals(&callback)) {
                    (*i)->reset();
                    m_cleanUnEnabled = true;
                    return true;
                }
            }
            return false;
        }

        bool contains(const NrEventCallback& callback) {
            for (auto i = m_vector->begin() ; i != m_vector->end() ; i++) {
                if ((*i)->isEquals(&callback)) {
                    return true;
                }
            }
            return false;
        }

        void cleanUnEnabled() {
            if (!m_cleanUnEnabled) {
                return;
            }

            for (auto i = m_vector->begin() ; i != m_vector->end() ; ) {
                if (!(*i)->isEnable()) {
                    NrEventCallback* cb = (*i);
                    i = m_vector->erase(i);
                    delete cb;
                } else {
                    i++;
                }
            }
            m_cleanUnEnabled = false;
        }

        bool isEmpty() const {
            return m_vector->empty();
        }

    public:
        bool m_cleanUnEnabled {false};
        std::vector<NrEventCallback*>* m_vector {nullptr};
    };

private:
    /**
     * 调用
     */
    template<typename T, bool isRetVoid = std::is_void<T>::value>
    class NrEventCallbackInvoker {
    public:
        static T run(NrEventCallbackList& cbList, sender_type sender, parameter_type parameter) {
            std::vector<NrEventCallback*>* callbacks = cbList.m_vector;
            typename std::vector<NrEventCallback*>::size_type length = callbacks->size();

            T retval {};

            /**
             * 注意：不要使用iterator遍历。
             * 在执行回调函数的过程中，如果用户有添加新的回调、删除已有回调，会导致iterator异常。
             * 因此，remove函数也不是真正的remove，只是reset为不可用
             */
            for (typename std::vector<NrEventCallback*>::size_type i = 0; i < length; i++) {
                if ((*callbacks)[i]->isEnable()) {
                    retval = (*callbacks)[i]->run(sender, parameter);
                }
            }
            cbList.cleanUnEnabled();
            return retval;
        }
    };

    template<typename T>
    class NrEventCallbackInvoker<T, true> {
    public:
        static void run(NrEventCallbackList& cbList, sender_type sender, parameter_type parameter) {
            std::vector<NrEventCallback*>* callbacks = cbList.m_vector;
            typename std::vector<NrEventCallback*>::size_type length = callbacks->size();

            /**
             * 注意：不要使用iterator遍历
             */
            for (typename std::vector<NrEventCallback*>::size_type i = 0 ; i < length ; i++) {
                if ((*callbacks)[i]->isEnable()) {
                    (*callbacks)[i]->run(sender, parameter);
                }
            }
            cbList.cleanUnEnabled();
        }
    };

public:
    /**
     * 成员函数指针
     */
    template<typename T>
    bool add(T* object, typename NrEventAdapter<retval_type(T::*)(sender_type, parameter_type)>::Callback callback) {
        if (object == nullptr || callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackComplex<T> c{};
        c.m_object = object;
        c.m_callback = callback;

        return m_list->add(c);
    }

    template<typename T>
    bool remove(T* object, typename NrEventAdapter<retval_type(T::*)(sender_type, parameter_type)>::Callback callback) {
        if (object == nullptr || callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackComplex<T> c{};
        c.m_object = object;
        c.m_callback = callback;

        return m_list->remove(c);
    }

    template<typename T>
    bool contains(T* object, typename NrEventAdapter<retval_type(T::*)(sender_type, parameter_type)>::Callback callback) {
        if (object == nullptr || callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackComplex<T> c{};
        c.m_object = object;
        c.m_callback = callback;

        return m_list->contains(c);
    }


public:
    /**
     * 普通函数指针
     */
    bool add(typename NrEventAdapter<retval_type(sender_type, parameter_type)>::Callback callback) {
        if (callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackSimple s{};
        s.m_callback = callback;

        return m_list->add(s);
    }

    bool remove(typename NrEventAdapter<retval_type(sender_type, parameter_type)>::Callback callback) {
        if (callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackSimple s{};
        s.m_callback = callback;

        return m_list->remove(s);
    }

    bool contains(typename NrEventAdapter<retval_type(sender_type, parameter_type)>::Callback callback) {
        if (callback == nullptr) {
            #ifdef NRSCRIPT_DEBUG
                NRSCRIPT_ASSERT(false);
            #endif
            return false;
        }

        NrEventCallbackSimple s{};
        s.m_callback = callback;

        return m_list->contains(s);
    }

public:
    /**
     * 触发事件
     */
    retval_type operator() (sender_type sender, parameter_type parameter) {
        return NrEventCallbackInvoker<retval_type>::run(*m_list, sender, parameter);
    }

    /**
     * 确认当前事件代理的函数指针的列表内容是否为空
     */
    bool isEmpty() const {
        return m_list->isEmpty();
    }

    public:
    /**
     * 默认构造函数
     */
    NrEvent() {
        m_list = new NrEventCallbackList();
    }

    ~NrEvent() {
        delete m_list;
    }

private:
    /**
     * 函数指针管理
     */
    NrEventCallbackList* m_list;
};

#endif
