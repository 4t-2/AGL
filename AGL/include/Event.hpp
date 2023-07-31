#pragma once

#include "RenderWindow.hpp"
#include "Vec.hpp"

namespace agl
{
	class Event
	{
		private:
			BaseWindow *window;
			BaseEvent baseEvent;

			char		 keymap[32];
			int			 rootx, rooty;
			int			 winx, winy;
			unsigned int maskReturn;

			bool shouldWindowClose = false;

			int _pointerButton = 0;
			std::string _keybuffer = "";

		public:
			const int &pointerButton = _pointerButton;
			const std::string &keybuffer = _keybuffer;

			void setWindow(RenderWindow window);

			bool windowClose();

			void poll();

			bool	 isKeyPressed(Key key);
			Vec<int, 2> getPointerWindowPosition();
			Vec<int, 2> getPointerRootPosition();
			bool	 isPointerButtonPressed(Button button);

			// \ character returned is in utf-8 format
			int currentKeyPressed(char key[2]);
	};
} // namespace agl
