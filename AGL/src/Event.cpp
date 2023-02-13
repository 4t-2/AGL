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
	else
	{
		xev = XEvent();
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

void agl::Event::poll(std::function<void(XEvent xev)> eventLoop)
{
	this->pollKeyboard();
	this->pollPointer();

	while(XPending(display))
	{
		XNextEvent(display, &xev);

		eventLoop(xev);
	}
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

agl::Vec<int, 2> agl::Event::getPointerWindowPosition()
{
	return {winx, winy};
}

agl::Vec<int, 2> agl::Event::getPointerRootPosition()
{
	return {rootx, rooty};
}

bool agl::Event::isPointerButtonPressed(int buttonMask)
{
	if (maskReturn & buttonMask)
	{
		return true;
	}

	return false;
}

bool agl::Event::currentKeyPressed(char *key)
{
	if (xev.type == KeyPress)
	{
		KeySym keysym;
		char test[1];

		XLookupString((XKeyEvent *)&xev, test, 1, &keysym, nullptr);

		*key = test[0];

		// need XOpenIM() and XCreateIC()
		// char buffer[32];
		// KeySym ignore;
		// Status return_status;
		// Xutf8LookupString(xic, &xev.xkey, buffer, 32, &ignore, &return_status);
		// printf("%s\n", buffer);
		// std::cout << (unsigned int)((unsigned char)buffer[0]) << '\n';
		// std::cout << "keyrecieved" << '\n';

		return true;
	}

	return false;
}
