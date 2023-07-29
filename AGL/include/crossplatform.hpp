#pragma once

#include "Vec.hpp"

#ifdef __linux__
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

namespace agl
{
	class BaseWindow
	{
		public:
			Display		*dpy;
			Window		 root;
			XVisualInfo *vi;
			Colormap	 cmap;
			long		 eventMask;
			Window		 win;
			GLXContext	 glc;

			Atom   wmDeleteMessage;
			GLuint VertexArrayID;

			PFNGLXSWAPINTERVALSGIPROC setSwapIntervalPointer;
	};

	class BaseEvent
	{
		public:
			Display *display;
			Window	 window;
			Atom	 wmDeleteMessage;
			XEvent	 xev;
			XIM		 xim;
			XIC		 xic;
	};
} // namespace agl

#endif

#ifdef _WIN32
#include <windows.h>

#endif

namespace agl
{
	void createWindow(BaseWindow &window, agl::Vec<int, 2> size, std::string title);
	void initGL(BaseWindow &window);

	void mapWindow(BaseWindow &window);
	void setSwapInterval(BaseWindow &window, int i);
	void setCursorShape(BaseWindow &window, unsigned int shape);

	void swapBuffers(BaseWindow &window);

	void closeWindow(BaseWindow &window);

	void setupEvent(BaseEvent &event, BaseWindow &window);
	int currentKeyPressed(BaseEvent &event, char buffer[2]);
	void pollEvents(BaseEvent &event, char keymap[32], agl::Vec<int, 2> &root, agl::Vec<int, 2> &win,
					unsigned int &maskReturn, bool &shouldWindowClose, std::string &keybuffer, int &pointerButton);
	bool isKeyPressed(BaseEvent&event, char keymap[32], int keysym);
} // namespace agl
