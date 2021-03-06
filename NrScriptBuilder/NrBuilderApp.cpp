﻿#include "NrBuilderFrame.h"
#include "NrBuilderApp.h"


NrBuilderApp::NrBuilderApp() {
}

NrBuilderApp::~NrBuilderApp() {
}

bool NrBuilderApp::initialize() {
    NrWindowBase::CreateParameter parameter {};
    parameter.bounds.width = 960;
    parameter.bounds.height = 544;
    parameter.caption = L"NrScript XML Builder";

    if (!m_builderFrame->create(parameter)) {
        return false;
    }

    m_builderFrame->centerScreen();
    m_builderFrame->show();
    return true;
}