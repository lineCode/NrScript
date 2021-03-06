﻿/**
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

#include "NrScript/base.h"
#include "NrScript/ui.h"

class NrControl::Impl {
    friend class NrControl;
public:
    /**
     * 默认构造函数
     */
    Impl(NrControl* owner) {
        m_self = owner;
        m_childrenPtr = new std::vector<NrControl*>();
    }

    ~Impl() {
        NRSCRIPT_ASSERT(false && "清理子控件");
    }

public:
    /**
     * 更新控件层级
     */
    void updateLayer(int layer) {
        m_layer = layer;

        for (auto i = m_childrenPtr->begin() ; i != m_childrenPtr->end() ; i++) {
            (*i)->updateLayer(m_layer + 1);
        }
    }

    void add(NrControl* control) {
        if (control == nullptr) {
            return;
        }

        if (control == m_self) {
            return;
        }

        NrControl* parent = control->getParent();
        if (parent == m_self) {
            return;
        }

        if (parent != nullptr) {
            parent->remove(control);
        }

        control->impl->m_parentPtr = m_self;
        m_childrenPtr->push_back(control);
    }

    void remove(NrControl* control) {
        if (control == nullptr) {
            return;
        }

        if (control == m_self) {
            return;
        }

        if (control->getParent() != m_self) {
            return;
        }

        for (auto i = m_childrenPtr->begin() ; i != m_childrenPtr->end() ; i++) {
            if ((*i) == control) {
                m_childrenPtr->erase(i);
                NRSCRIPT_ASSERT(false && "清理空间属性； delete 释放内存");
                break;
            }
        }
    }

    NrControl* getParent() {
        return m_parentPtr;
    }

private:
    /**
     * 桥接所属
     */
    NrControl* m_self {nullptr};

    /**
     * 父控件
     */
    NrControl* m_parentPtr {nullptr};

    /**
     * 层级
     */
    int m_layer {0};

    /**
     * 子控件
     */
    std::vector<NrControl*>* m_childrenPtr {nullptr};
};

NrControl::NrControl() {
    this->initialize();
    impl = new Impl(this);
}

NrControl::~NrControl() {
    this->finalize();
    delete impl;
}

void NrControl::add(NrControl* control) {
    impl->add(control);
}

void NrControl::remove(NrControl* control) {
    impl->remove(control);
}

NrControl* NrControl::getParent() {
    return impl->getParent();
}

void NrControl::updateLayer(int layer) {
    impl->updateLayer(layer);
}

/**
 * 私有函数、非桥接函数在下面实现
 */
void NrControl::initialize() {
    /**
     * 改做pugixml了。
     */
    //this->propText.acceptString("text=");
    //this->defineProperty("text", propText);
    //this->defineProperty("textcolor", propTextColor);

    //this->defineProperty("text", );

    //
}

void NrControl::finalize() {
}