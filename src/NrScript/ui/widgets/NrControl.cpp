﻿#include "NrScript/base.h"
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

        auto iter = m_childrenPtr->begin();
        for ( ; iter != m_childrenPtr->end() ; iter++) {
            if ((*iter) == control) {
                m_childrenPtr->erase(iter);
                
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
    this->initialEvents();
    impl = new Impl(this);
}

NrControl::~NrControl() {
    this->finalizeEvents();
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

void NrControl::OnPaint(NrControl* sender, NrReserved reserved) {
    NRSCRIPT_UNREFERENCED_PARAMETER(sender);
    NRSCRIPT_UNREFERENCED_PARAMETER(reserved);
}

/**
 * 私有函数、非桥接函数在下面实现
 */
void NrControl::initialEvents() {
    eOnPaintPtr = new NrEvent<void(NrControl*, NrReserved)>();

    eOnPaintPtr->add(this, &NrControl::OnPaint);
}

void NrControl::finalizeEvents() {
    eOnPaintPtr->remove(this, &NrControl::OnPaint);

    delete eOnPaintPtr;
}