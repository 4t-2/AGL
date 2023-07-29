#include "../include/external.hpp"

#ifdef _WIN32

static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	wcex.cbSize		   = sizeof(WNDCLASSEX);
	wcex.style		   = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc   = (WNDPROC)wndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance	   = hInstance;
	wcex.hIcon		   = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor	   = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = window.className;
	wcex.hIconSm	   = NULL;
	RegisterClassExW(&wcex);

	// create window

	DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	window.hndl = CreateWindowW(window.className, window.className, style, 0, 0, size.x, size.y, nullptr, nullptr,
								window.hInstance, nullptr);
}

void agl::initGL(BaseWindow &window)
{
	// create opengl context
	window.deviceContext = GetDC(window.hndl);
	int					  pixelFormat;
	PIXELFORMATDESCRIPTOR pixelFormatDesc;

	/* initialize bits to 0 */
	memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelFormatDesc.nSize	   = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion   = 1;
	pixelFormatDesc.dwFlags	   = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
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

void agl::createWindow(BaseWindow &window, agl::Vec<int, 2> size, std::string title)
{
	GLint attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	window.dpy		 = XOpenDisplay(NULL);
	window.root		 = DefaultRootWindow(window.dpy);
	window.vi		 = glXChooseVisual(window.dpy, 0, attribute);
	window.cmap		 = XCreateColormap(window.dpy, window.root, window.vi->visual, AllocNone);
	window.eventMask = ExposureMask | KeyPressMask | KeyReleaseMask;
	XSetWindowAttributes swa;
	swa.colormap   = window.cmap;
	swa.event_mask = window.eventMask;

	window.win = XCreateWindow(window.dpy, window.root, 0, 0, size.x, size.y, 0, window.vi->depth, InputOutput,
							   window.vi->visual, CWColormap | CWEventMask,
							   &swa); // window is created and the function returns an id

	XStoreName(window.dpy, window.win, title.c_str());
}

void agl::initGL(agl::BaseWindow &window)
{
	window.glc = glXCreateContext(window.dpy, window.vi, NULL, GL_TRUE);
	glXMakeCurrent(window.dpy, window.win, window.glc); // bind it to the window

	glewInit();

	window.setSwapIntervalPointer = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte *)"glXSwapIntervalSGI");
}

void agl::mapWindow(agl::BaseWindow &window)
{
	XMapWindow(window.dpy, window.win);
}

void agl::setSwapInterval(agl::BaseWindow &window, int i)
{
	window.setSwapIntervalPointer(i);
}

void agl::setCursorShape(agl::BaseWindow &window, unsigned int shape)
{
	Cursor c;
	c = XCreateFontCursor(window.dpy, shape);
	XDefineCursor(window.dpy, window.win, c);
}

void agl::swapBuffers(agl::BaseWindow &window)
{
	glXSwapBuffers(window.dpy, window.win);
}

void agl::closeWindow(agl::BaseWindow &window)
{
	glXMakeCurrent(window.dpy, None, NULL);	   // release gl binding to window
	glXDestroyContext(window.dpy, window.glc); // destroy context

	XFree(window.vi);						// delete the visual info data
	XDestroyWindow(window.dpy, window.win); // kill window
	XFreeColormap(window.dpy, window.cmap); // free colormap
	XCloseDisplay(window.dpy);				// close display
}

void agl::setupEvent(agl::BaseEvent &event, agl::BaseWindow &window)
{
	event.display = window.dpy;
	event.window  = window.win;

	event.wmDeleteMessage = XInternAtom(event.display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(event.display, event.window, &event.wmDeleteMessage, 1);

	event.xim = XOpenIM(window.dpy, nullptr, nullptr, nullptr);
	event.xic = XCreateIC(event.xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);

	XSetICFocus(event.xic);

	XSelectInput(window.dpy, window.win, ButtonPressMask | KeyPressMask);
}

int agl::currentKeyPressed(agl::BaseEvent &event, char buffer[2])
{
	KeySym keysym;
	int	   bytes_buffer = 2;
	Status status;
	int	   len = Xutf8LookupString(event.xic, &event.xev.xkey, buffer, bytes_buffer, &keysym, &status);

	return len;
}

void agl::pollEvents(agl::BaseEvent &event, char keymap[32], agl::Vec<int, 2> &root, agl::Vec<int, 2> &win,
					 unsigned int &maskReturn, bool &shouldWindowClose, std::string &keybuffer, int &pointerButton)
{
	Window p;

	XQueryKeymap(event.display, keymap);
	XQueryPointer(event.display, event.window, &p, &p, &root.x, &root.y, &win.x, &win.y, &maskReturn);
	
	while (XPending(event.display))
	{
		XNextEvent(event.display, &event.xev);

		switch (event.xev.type)
		{
			case ClientMessage:
				shouldWindowClose = (event.xev.xclient.data.l[0] == event.wmDeleteMessage);
			case ButtonPress:
				pointerButton = event.xev.xbutton.button;
			case KeyPress:
				char key[2];
				if (int size = agl::currentKeyPressed(event, key))
				{
					keybuffer += std::string().append(key, size);
				}
		}
	}

	event.xev = XEvent();
}

bool agl::isKeyPressed(agl::BaseEvent&event, char keymap[32], int keysym)
{
	int keycode = XKeysymToKeycode(event.display, keysym);
	if (keymap[keycode / 8] & (0x1 << (keycode % 8)))
	{
		return true;
	}

	return false;
}

#endif
