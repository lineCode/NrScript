#include <Windows.h>
#include "NrBuilderApp.h"

class NrMy : public NrControl {
    
};

//NrWidgetStringCreator<NrMy> kMy(L"My");
//NrWidgetStringCreator<NrMy> kMy2(L"My2");
//NrWidgetStringCreator<NrMy> kMy23(L"M3y");
//NrWidgetStringCreator<NrMy> kMy3(L"M4y");
//NrWidgetStringCreator<NrMy> kMy4(L"M5y");
//NrWidgetStringCreator<NrMy> kMy5(L"M6y");
//NrWidgetStringCreator<NrMy> kMy6(L"M7y");
//NrWidgetStringCreator<NrMy> kMy7(L"M8y");
//NrWidgetStringCreator<NrMy> kMy8(L"M9y");
//NrWidgetStringCreator<NrMy> kMy9(L"M0y");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();

    MSG msg = {nullptr};
    while (::GetMessage(&msg, nullptr, NULL, NULL))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return 0;
}