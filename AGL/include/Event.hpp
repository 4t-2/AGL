#pragma once

#include "RenderWindow.hpp"
#include "Vec2i.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>

namespace agl
{
	class Event
	{
		private:
			Display *display;
			Window	 window;
			Atom wmDeleteMessage;

			XEvent		 xev;
			char		 keymap[32];
			int			 rootx, rooty;
			int			 winx, winy;
			unsigned int maskReturn;

		public:
			void setWindow(RenderWindow window);

			bool windowClose();

			void pollWindow();
			void pollKeyboard();
			void pollPointer();

			bool	 isKeyPressed(int keysym);
			Vec2i getPointerWindowPosition();
			Vec2i getPointerRootPosition();
			bool	 isPointerButtonPressed(int buttonMask);
	};
} // namespace agl
