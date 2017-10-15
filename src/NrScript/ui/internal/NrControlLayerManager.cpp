#include "NrScript/base.h"
#include "NrScript/ui.h"

class NrControlLayerManager::Impl {
public:
    /**
     * 默认构造
     */
    Impl() {
    
    }

    ~Impl() {
    
    }

public:
    /**
     * 更新控件层级
     */
    void update(NrControl* root) {
        if (root == nullptr) {
            return;
        }
        root->updateLayer(0);
        
    }

private:

};

NrControlLayerManager::NrControlLayerManager() {
    impl = new Impl();
}

NrControlLayerManager::~NrControlLayerManager() {
    delete impl;
}

void NrControlLayerManager::update(NrControl* root) {
    impl->update(root);
}