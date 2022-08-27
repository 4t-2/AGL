#include "RenderWindow.hpp"
#include <X11/Xlib.h>

namespace agl
{
	class Keyboard
	{
		private:
			Display *display;

		public:

			void linkRenderWindow(RenderWindow window);
			int	 isKeyPressed(int keysym);
	};
} // namespace agl
