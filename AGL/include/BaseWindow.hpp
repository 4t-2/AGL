#ifdef _WIN32
#include <windows.h>
namespace agl
{
    class BaseWindow
    {
    public:
        HINSTANCE hInstance;
        HWND hndl;
        HDC deviceContext;
        HGLRC renderContext;
        LPCWSTR className;
    };
}
#endif
#ifdef __linux__
#endif