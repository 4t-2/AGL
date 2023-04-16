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

			bool shouldWindowClose = false;

			XIM xim;
			XIC xic;

			int _pointerButton = 0;
			std::string _keybuffer = "";

		public:
			const int &pointerButton = _pointerButton;
			const std::string &keybuffer = _keybuffer;

			void setWindow(RenderWindow window);

			bool windowClose();

			void pollWindow();
			void pollKeyboard();
			void pollPointer();
			void pollPressedKeys();

			void poll(std::function<void(XEvent xev)> eventLoop);
			void poll();

			bool	 isKeyPressed(int keysym);
			Vec<int, 2> getPointerWindowPosition();
			Vec<int, 2> getPointerRootPosition();
			bool	 isPointerButtonPressed(int buttonMask);

			// \ character returned is in utf-8 format
			int currentKeyPressed(char key[2]);

			XEvent getXev()
			{
				return xev;
			}
	};
} // namespace agl
