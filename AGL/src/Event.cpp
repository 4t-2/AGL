#include "../include/Event.hpp"
#include "../include/RenderWindow.hpp"

void agl::Event::setWindow(agl::RenderWindow window)
{
	this->display = window.getDisplay();
	this->window  = window.getWindow();

	this->wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(this->display, this->window, &this->wmDeleteMessage, 1);

	return;
}

bool agl::Event::windowClose()
{
	return (xev.xclient.data.l[0] == wmDeleteMessage);
}

void agl::Event::pollWindow()
{
	if (XPending(display))
	{
		XNextEvent(display, &xev);
	}
}

void agl::Event::pollKeyboard()
{
	XQueryKeymap(display, keymap);
	return;
}

void agl::Event::pollPointer()
{
	Window rootReturn, childReturn;

	XQueryPointer(display, window, &rootReturn, &childReturn, &rootx, &rooty, &winx, &winy, &maskReturn);

	return;
}

bool agl::Event::isKeyPressed(int keysym)
{
	int keycode = XKeysymToKeycode(this->display, keysym);
	if (keymap[keycode / 8] & (0x1 << (keycode % 8)))
	{
		return true;
	}

	return false;
}

agl::Int2 agl::Event::getPointerWindowPosition()
{
	return {winx, winy};
}

agl::Int2 agl::Event::getPointerRootPosition()
{
	return {rootx, rooty};
}

bool agl::Event::isPointerButtonPressed(int buttonMask)
{
	if(maskReturn & buttonMask)
	{
		return true;
	}

	return false;
}
