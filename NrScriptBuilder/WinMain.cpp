#include <Windows.h>
#include "NrBuilderApp.h"
#include <functional>

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd) {
    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();

    char32_t* m = U"Hello, world!";
    char32_t* m2 = U"Hello, world!";
    int n = std::char_traits<char32_t>::compare(m, m2, std::char_traits<char32_t>::length(m));

    MSG msg = {0};
    while (::GetMessage(&msg, NULL, NULL, NULL))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return 0;
}