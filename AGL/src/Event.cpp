#include "../include/Event.hpp"
#include "../include/RenderWindow.hpp"

#include <bitset>

void agl::Event::setWindow(agl::RenderWindow window)
{
	this->display = window.getDisplay();
	this->window  = window.getWindow();

	this->wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(this->display, this->window, &this->wmDeleteMessage, 1);

	xim = XOpenIM(window.getDisplay(), nullptr, nullptr, nullptr);
	xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);

	XSetICFocus(xic);

	XSelectInput(window.getDisplay(), window.getWindow(), ButtonPressMask | KeyPressMask);

	return;
}

bool agl::Event::windowClose()
{
	return shouldWindowClose;
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

	while (XPending(display))
	{
		XNextEvent(display, &xev);

		eventLoop(xev);
	}

	xev = XEvent();
}

void agl::Event::poll()
{
	_keybuffer	   = "";
	_pointerButton = 0;

	this->poll([&](XEvent xev) {
		switch (xev.type)
		{
			case ClientMessage:
				shouldWindowClose = (xev.xclient.data.l[0] == wmDeleteMessage);
			case ButtonPress:
				_pointerButton = xev.xbutton.button;
			case KeyPress:
				char key[2];
				if (int size = this->currentKeyPressed(key))
				{
					_keybuffer += std::string().append(key, size);
				}
		}
	});
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

int agl::Event::currentKeyPressed(char buffer[2])
{
	KeySym keysym;
	int	   bytes_buffer = 2;
	Status status;
	int	   len = Xutf8LookupString(xic, &xev.xkey, buffer, bytes_buffer, &keysym, &status);

	// switch (status)
	// {
	//
	// 	case XBufferOverflow:
	// 		// buffer too small to store character
	// 		return false;
	//
	// 	case XLookupChars:
	// 		// returned character but not keysym
	// 		return true;
	//
	// 	case XLookupBoth:
	// 		// returned both
	// 		// std::cout << std::string().append(buffer, 2) << '\n';
	// 		return true;
	//
	// 	case XLookupKeySym:
	// 		// returned a keysym without a character
	// 		return false;
	//
	// 	default:
	// 		return false;
	// }

	return len;
}
