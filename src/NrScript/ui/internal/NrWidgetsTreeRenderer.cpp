#include "NrScript/base.h"
#include "NrScript/ui.h"

NrWidgetsTreeRenderer::NrWidgetsTreeRenderer() {
}

NrWidgetsTreeRenderer::~NrWidgetsTreeRenderer() {
}

void NrWidgetsTreeRenderer::doTraversal(NrControl* root, int width, int height) {
    if (root == nullptr) {
        return;
    }

    if (width <= 0 || height <= 0) {
        return;
    }


}