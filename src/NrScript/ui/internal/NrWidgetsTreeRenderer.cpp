#include "NrScript/base.h"
#include "NrScript/ui.h"

NrWidgetsTreeRenderer::NrWidgetsTreeRenderer() {
}

NrWidgetsTreeRenderer::~NrWidgetsTreeRenderer() {
}

void NrWidgetsTreeRenderer::setRenderTarget(NrControl* root) {
    m_root = root;
}

void NrWidgetsTreeRenderer::doTraversal(int width, int height) {
    
}