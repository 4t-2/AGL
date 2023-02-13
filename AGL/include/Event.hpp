#pragma once

#include "RenderWindow.hpp"
#include "Vec.hpp"
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

			void poll(std::function<void(XEvent xev)> eventLoop);

			bool	 isKeyPressed(int keysym);
			Vec<int, 2> getPointerWindowPosition();
			Vec<int, 2> getPointerRootPosition();
			bool	 isPointerButtonPressed(int buttonMask);

			bool currentKeyPressed(char *key);

			XEvent getXev()
			{
				return xev;
			}
	};
} // namespace agl
