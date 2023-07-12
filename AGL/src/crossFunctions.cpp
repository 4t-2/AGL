#include "../include/crossFunctions.hpp"

#ifdef _WIN32

static LRESULT CALLBACK
wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	return result;
}

void agl::createWindow(BaseWindow &window, agl::Vec<int, 2> position, agl::Vec<int, 2> size, std::string title)
{
	// get handle
	HINSTANCE hInstance = GetModuleHandle(NULL);

	window.className = std::wstring(title.begin(), title.end()).c_str();

	// register
	WNDCLASSEXW wcex;
	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = window.className;
	wcex.hIconSm = NULL;
	RegisterClassExW(&wcex);

	// create window

	DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	window.hndl = CreateWindowW(window.className, window.className, style, 0, 0, size.x, size.y, nullptr, nullptr, window.hInstance, nullptr);
}

void agl::initGL(BaseWindow &window)
{
	// create opengl context
	window.deviceContext = GetDC(window.hndl);
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pixelFormatDesc;

	/* initialize bits to 0 */
	memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;

	pixelFormat = ChoosePixelFormat(window.deviceContext, &pixelFormatDesc);
	SetPixelFormat(window.deviceContext, pixelFormat, &pixelFormatDesc);
	window.renderContext = wglCreateContext(window.deviceContext);

	// make context current
	wglMakeCurrent(window.deviceContext, window.renderContext);
}

void agl::mapWindow(BaseWindow &window)
{
	ShowWindow(window.hndl, 0);
	SetWindowPos(window.hndl, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

#endif

#ifdef __linux__
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#endif