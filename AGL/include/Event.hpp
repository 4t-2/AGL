#pragma once

#include "RenderWindow.hpp"
#include "Int2.hpp"
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
			Int2 getPointerWindowPosition();
			Int2 getPointerRootPosition();
			bool	 isPointerButtonPressed(int buttonMask);
	};
} // namespace agl
