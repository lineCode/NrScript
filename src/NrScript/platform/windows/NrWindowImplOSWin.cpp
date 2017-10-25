#include <tchar.h>

#include "NrScript/base.h"
#include "NrScript/ui.h"
#include "NrScript/skia.h"
#include "NrScript/platform/windows/NrWindowImplOSWin.h"

static TCHAR kHwndWindowClassName[] = _T("NrScriptWindowClass");
static TCHAR kOSWindowDefaultIcon[] = _T("NrScriptDefaultIcon");

/**
 * 获取当前模块句柄
 */
static HMODULE GetSelfModuleHandle() {
    MEMORY_BASIC_INFORMATION mbi = {0};

    if (::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) {
        return (HMODULE)mbi.AllocationBase;
    }
    else {
        return nullptr;
    }
}

class NrWindowImplOSWin::Impl : public NrWindowBase {
public:
    /**
     * 默认构造函数
     */
    Impl(NrWindowImplOSWin* owner): m_pOwner(owner){
        m_renderer = new NrWidgetsTreeRenderer();
    }

    /**
     * 默认析构函数
     */
    ~Impl() {
        delete m_renderer;
    }

private:
    /**
     * 窗口回调过程
     */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        Impl* self = nullptr;

        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
            if (pCreateStruct && pCreateStruct->lpCreateParams) {
                ::SetProp(hWnd, kHwndWindowClassName, (HANDLE)pCreateStruct->lpCreateParams);
            }
        }

        self = (Impl*)::GetProp(hWnd, kHwndWindowClassName);
        if (self) {
            self->m_Hwnd = hWnd;

            if (uMsg == WM_NCDESTROY) {
                ::RemoveProp(hWnd, kHwndWindowClassName);
            }
            return self->handleMessage(hWnd, uMsg, wParam, lParam);
        }
        return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

public:
    /**
     * 窗口过程
     */
    LRESULT handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        /**
         * 此处不要添加任何代码
         */
        return m_pOwner->handleMessage(hWnd, uMsg, wParam, lParam);
    }

    HWND getHwnd() {
        return m_Hwnd;
    }

public:
    /**
     * 创建窗口
     */
    bool create(const NrWindowCreateParameter& parameter) override {
        static bool kNrScriptWindowClassRegistered = false;
        HINSTANCE hInstance = ::GetModuleHandle(0);

        if (!kNrScriptWindowClassRegistered) {
            WNDCLASSEX wndClassEx = {0};
            wndClassEx.cbClsExtra = sizeof(void*);
            wndClassEx.cbSize = sizeof(WNDCLASSEX);
            wndClassEx.cbWndExtra = sizeof(void*);
            wndClassEx.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1);
            wndClassEx.hInstance = hInstance;
            wndClassEx.lpfnWndProc = &Impl::WndProc;
            wndClassEx.lpszClassName = kHwndWindowClassName;
            wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

            wndClassEx.hCursor = ::LoadCursor(NULL, IDC_ARROW);
            wndClassEx.hIcon = ::LoadIcon(GetSelfModuleHandle(), kOSWindowDefaultIcon);
            wndClassEx.hIconSm = ::LoadIcon(GetSelfModuleHandle(), kOSWindowDefaultIcon);
            wndClassEx.lpszMenuName;

            if (RegisterClassEx(&wndClassEx)) {
                kNrScriptWindowClassRegistered = true;
            }
        }

        DWORD styleEx = WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES;
        DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

        if (kNrScriptWindowClassRegistered) {
            RECT rSrc {};
            rSrc.right = parameter.bounds.width;
            rSrc.bottom = parameter.bounds.height;

            ::AdjustWindowRectEx(&rSrc, style, FALSE, styleEx);

            return (::CreateWindowEx(styleEx, 
                kHwndWindowClassName, 
                NULL, 
                style, 
                parameter.bounds.x, parameter.bounds.y, rSrc.right - rSrc.left, rSrc.bottom - rSrc.top, 
                NULL, NULL, hInstance, this) != NULL);
        }
        
        return false;
    }

    void setContentView(NrControl* root) override {
        m_renderer->setRenderTarget(root);
    }

    bool isActive() const override {
        return false;
    }

    NrWindowBase* getNativeWindow() override {
        return m_pOwner;
    }

    void show() override {
        ::ShowWindow(m_Hwnd, SW_SHOWNORMAL);
    }

    void showInactive() override {
        ::ShowWindow(m_Hwnd, SW_SHOWNOACTIVATE);
    }

    void setBounds(const NrRect& bounds) override {
        RECT r = {0};
        r.right = bounds.width;
        r.bottom = bounds.height;

        DWORD styleEx = (DWORD)::GetWindowLongPtr(m_Hwnd, GWL_EXSTYLE);
        DWORD style = (DWORD)::GetWindowLongPtr(m_Hwnd, GWL_STYLE);

        ::AdjustWindowRectEx(&r, style, FALSE, styleEx);

        ::MoveWindow(m_Hwnd, bounds.x, bounds.y, r.right - r.left, r.bottom - r.top, TRUE);
    }

    NrRect getBounds() const override {
        RECT r = {0};
        ::GetWindowRect(m_Hwnd, &r);

        NrRect retval = {0};
        retval.x = r.left;
        retval.y = r.top;

        ::GetClientRect(m_Hwnd, &r);
        retval.width = r.right - r.left;
        retval.height = r.bottom - r.top;

        return retval;
    }

public:
    /**
     * 获取渲染器
     */
    NrWidgetsTreeRenderer* getRenderer() {
        return m_renderer;
    }

private:
    /**
     * 窗口句柄
     */
    HWND m_Hwnd {0};

    /**
     * 桥接容器
     */
    NrWindowImplOSWin* m_pOwner {nullptr};

    /**
     * 渲染器
     */
    NrWidgetsTreeRenderer* m_renderer {nullptr};
};

NrWindowImplOSWin::NrWindowImplOSWin(NrWindowBase* sendHandler) {
#ifdef NRSCRIPT_DEBUG
    if (sendHandler == nullptr) {
        NRSCRIPT_ASSERT(false);
    }
#endif
    initialEvents();
    m_pSendHandler = sendHandler;
    impl = new Impl(this);
}

NrWindowImplOSWin::~NrWindowImplOSWin() {
    finalizeEvents();
    m_pSendHandler = nullptr;
    delete impl;
}

HWND NrWindowImplOSWin::getHwnd() {
    return dynamic_cast<NrWindowImplOSWin::Impl*>(impl)->getHwnd();
}

void NrWindowImplOSWin::setContentView(NrControl* root) {
    impl->setContentView(root);
}

bool NrWindowImplOSWin::create(const NrWindowCreateParameter& parameter) {
    return impl->create(parameter);
}

NrWindowBase* NrWindowImplOSWin::getNativeWindow() {
    return impl->getNativeWindow();
}

bool NrWindowImplOSWin::isActive() const {
    return impl->isActive();
}

void NrWindowImplOSWin::show() {
    return impl->show();
}

void NrWindowImplOSWin::showInactive() {
    return impl->showInactive();
}

void NrWindowImplOSWin::setBounds(const NrRect& bounds) {
    return impl->setBounds(bounds);
}

NrRect NrWindowImplOSWin::getBounds() const {
    return impl->getBounds();
}

/**
 * 私有函数，非桥接函数都在下面书写
 */

void NrWindowImplOSWin::initialEvents() {
    eOnMessagePtr = new NrEvent<LRESULT(NrWindowImplOSWin*, MESSAGE&)>();
    eOnMessagePtr->add(this, &NrWindowImplOSWin::OnMessage);
}

void NrWindowImplOSWin::finalizeEvents() {
    eOnMessagePtr->remove(this, &NrWindowImplOSWin::OnMessage);
    delete eOnMessagePtr;
}

LRESULT NrWindowImplOSWin::handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    MESSAGE msg {hWnd, uMsg, wParam, lParam, false};
    
    /**
     * 渲染器相关的功能
     */
    NrWidgetsTreeRenderer* renderer =
        dynamic_cast<NrWindowImplOSWin::Impl*>(impl)->getRenderer();
    
    switch (uMsg) {
    case WM_PAINT:
        {
            PAINTSTRUCT ps = {0};
            ::BeginPaint(hWnd, &ps);
            if (renderer) {
                SkCanvas* canvas = new SkCanvas();
            }
            ::Rectangle(ps.hdc, 10, 10, 50, 50);

            ::EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        {
            int i = 0;
        }
        break;
    }

    /**
     * 消息分发
     */
    if (!eOnMessagePtr->isEmpty()) {
        LRESULT retval = (*eOnMessagePtr)(this, msg);

        if (msg.handled) {
            return retval;
        }
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT NrWindowImplOSWin::OnMessage(NrWindowImplOSWin* sender, MESSAGE& msg) {
    if (sender != this) {
        return NULL;
    }
    NrWindowBase::CommonEvents* pEvents = 
        dynamic_cast<NrWindowBase::CommonEvents*>(m_pSendHandler);

    switch (msg.uMsg) {
    case WM_CREATE:
        {
            if (pEvents && !pEvents->eOnCreate.isEmpty()) {
                pEvents->eOnCreate(m_pSendHandler, 0);
            }
        }
        break;
    case WM_CLOSE:
        {
            /**
             * MSDN : 如果用户不接管此函数，即
             * case WM_CLOSE:
             *    return ::DefWindowProc(...);
             *
             * 那么DefWindowProc会调用DestroyWindow销毁窗口
             */
            bool bCloseable = false;
            if (pEvents && !pEvents->eOnClose.isEmpty()) {
                pEvents->eOnClose(m_pSendHandler, bCloseable);
            }

            if (!bCloseable) {
                msg.handled = true;
            }
        }
        break;
    case WM_DESTROY:
        {
            if (pEvents && !pEvents->eOnDestroy.isEmpty()) {
                pEvents->eOnDestroy(m_pSendHandler, 0);
            }
        }
        break;
    case WM_SIZE:
        {
            if (pEvents && !pEvents->eOnSize.isEmpty()) {
                pEvents->eOnSize(m_pSendHandler, getBounds());
            }
        }
        break;
    }
    return NULL;
}