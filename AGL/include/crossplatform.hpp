#pragma once

#include "Vec.hpp"

#ifdef __linux__a

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

// #ifdef _WIN32

#include <GLFW/glfw3.h>

namespace agl
{
	class BaseWindow
	{
		public:
			GLFWwindow *window;
	};

	class BaseEvent
	{
		public:
			GLFWwindow *window;
	};
} // namespace agl

// #endif

namespace agl
{
	class Key
	{
		public:
			int code;

			static const Key Space;
			static const Key Apostrophe;
			static const Key Comma;
			static const Key Minus;
			static const Key Period;
			static const Key Slash;
			static const Key Num0;
			static const Key Num1;
			static const Key Num2;
			static const Key Num3;
			static const Key Num4;
			static const Key Num5;
			static const Key Num6;
			static const Key Num7;
			static const Key Num8;
			static const Key Num9;
			static const Key Semicolon;
			static const Key Equal;
			static const Key A;
			static const Key B;
			static const Key C;
			static const Key D;
			static const Key E;
			static const Key F;
			static const Key G;
			static const Key H;
			static const Key I;
			static const Key J;
			static const Key K;
			static const Key L;
			static const Key M;
			static const Key N;
			static const Key O;
			static const Key P;
			static const Key Q;
			static const Key R;
			static const Key S;
			static const Key T;
			static const Key U;
			static const Key V;
			static const Key W;
			static const Key X;
			static const Key Y;
			static const Key Z;
			static const Key LeftBracket;
			static const Key Backslash;
			static const Key RightBracket;
			static const Key Grave;
			static const Key Escape;
			static const Key Return;
			static const Key Tab;
			static const Key Backspace;
			static const Key Insert;
			static const Key Delete;
			static const Key Right;
			static const Key Left;
			static const Key Down;
			static const Key Up;
			static const Key PageUp;
			static const Key PageDown;
			static const Key Home;
			static const Key End;
			static const Key CapsLock;
			static const Key ScrollLock;
			static const Key NumLock;
			static const Key PrintScreen;
			static const Key Pause;
			static const Key F1;
			static const Key F2;
			static const Key F3;
			static const Key F4;
			static const Key F5;
			static const Key F6;
			static const Key F7;
			static const Key F8;
			static const Key F9;
			static const Key F10;
			static const Key F11;
			static const Key F12;
			static const Key F13;
			static const Key F14;
			static const Key F15;
			static const Key F16;
			static const Key F17;
			static const Key F18;
			static const Key F19;
			static const Key F20;
			static const Key F21;
			static const Key F22;
			static const Key F23;
			static const Key F24;
			static const Key F25;
			static const Key LeftShift;
			static const Key LeftControl;
			static const Key LeftAlt;
			static const Key LeftSuper;
			static const Key RightShift;
			static const Key RightControl;
			static const Key RightAlt;
			static const Key RightSuper;
	};

	class Button
	{
		public:
			int code;

			static const Button Left;
			static const Button Middle;
			static const Button Right;
	};

	class CursorType
	{
		public:
			int code;
			
			static const CursorType Arrow;
			static const CursorType Beam;
			static const CursorType Crosshair;
			static const CursorType Hand;
			static const CursorType HorResize;
			static const CursorType VerResize;
	};

	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
		Null
	};

	class WindowState
	{
		public:
			agl::Vec<int, 2> size;
			agl::Vec<int, 2> pos;
	};

	void createWindow(BaseWindow &window, agl::Vec<int, 2> size, std::string title);
	void initGL(BaseWindow &window);

	void mapWindow(BaseWindow &window);
	void setSwapInterval(BaseWindow &window, int i);
	void setCursorShape(BaseWindow &window, CursorType shape);

	void swapBuffers(BaseWindow &window);

	void closeWindow(BaseWindow &window);

	void setupEvent(BaseEvent &event, BaseWindow &window);
	int	 currentKeyPressed(BaseEvent &event, char buffer[2]);
	void pollEvents(BaseEvent &event, char keymap[32], agl::Vec<int, 2> &root, agl::Vec<int, 2> &win,
					unsigned int &maskReturn, bool &shouldWindowClose, std::string &keybuffer, Direction &scroll);
	bool isKeyPressed(BaseEvent &event, char keymap[32], Key key);
	bool isButtonPressed(BaseEvent &event, int maskReturn, Button button);

	WindowState getWindowState(BaseWindow &window);
} // namespace agl
