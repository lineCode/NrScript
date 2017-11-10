#include <Windows.h>
#include "NrBuilderApp.h"
#include <functional>

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd) {
    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();
    {
        char* msg = u8"体系结构";
        msg = "";
    }
    MSG msg = {0};
    while (::GetMessage(&msg, NULL, NULL, NULL))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return 0;
}