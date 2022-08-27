#include "../include/Keyboard.hpp"
#include <X11/Xlib.h>

void agl::Keyboard::linkRenderWindow(agl::RenderWindow window)
{
	this->display = window.getDisplay();
}

int agl::Keyboard::isKeyPressed(int keysym)
{
	char keymap[32];
	XQueryKeymap(this->display, keymap);

	int keycode = XKeysymToKeycode(display, keysym);

	if (keymap[keycode / 8] & (0x1 << (keycode % 8)))
	{

		return 1;
	}

	return 0;
}
