#include <Windows.h>
#include "NrBuilderApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();
    {
        NrString msg = L"中国人";
        NrCharsUTF8 s = msg.toUTF8();
        NrCharsUTF8 ss = s;
        NrCharsUTF8 bb = NrCharsUTF8::fromUTF8Bytes(ss);
        NrString a = NrCharsUTF8::fromUTF8Bytes(ss).toString();

        MessageBoxA(0,bb.toString().toChars(),0,0);
    }
    MSG msg = {0};
    while (::GetMessage(&msg, NULL, NULL, NULL))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return 0;
}