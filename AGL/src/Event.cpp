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
	_scroll = Direction::Null;

	agl::pollEvents(baseEvent, keymap, root, win, maskReturn, shouldWindowClose, _keybuffer, _scroll);

	rootx = root.x;
	rooty = root.y;

	winx = win.x;
	winy = win.y;
}

bool agl::Event::isKeyPressed(Key key)
{
	return agl::isKeyPressed(baseEvent, keymap, key);
}

agl::Vec<int, 2> agl::Event::getPointerWindowPosition()
{
	return {winx, winy};
}

agl::Vec<int, 2> agl::Event::getPointerRootPosition()
{
	return {rootx, rooty};
}

bool agl::Event::isPointerButtonPressed(agl::Button button)
{
	return agl::isButtonPressed(baseEvent, maskReturn, button);
}

int agl::Event::currentKeyPressed(char buffer[2])
{
	return agl::currentKeyPressed(baseEvent, buffer);
}
