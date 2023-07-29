#include "../include/Event.hpp"
#include "../include/RenderWindow.hpp"

#include <bitset>

void agl::Event::setWindow(agl::RenderWindow window)
{
	agl::setupEvent(baseEvent, window.baseWindow);

	return;
}

bool agl::Event::windowClose()
{
	return shouldWindowClose;
}

void agl::Event::poll()
{
	agl::Vec<int, 2> root;
	agl::Vec<int, 2> win;

	agl::pollEvents(baseEvent, keymap, root, win, maskReturn, shouldWindowClose, _keybuffer, _pointerButton);

	rootx = root.x;
	rooty = root.y;

	winx = win.x;
	winy = win.y;
}

bool agl::Event::isKeyPressed(int keysym)
{
	return agl::isKeyPressed(baseEvent, keymap, keysym);
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
	return agl::currentKeyPressed(baseEvent, buffer);
}
