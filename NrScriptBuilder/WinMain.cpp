#include <Windows.h>
#include "NrBuilderApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();

    MSG msg = {0};
    while (::GetMessage(&msg, NULL, NULL, NULL))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return 0;
}