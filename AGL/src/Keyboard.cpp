#include "../include/Keyboard.hpp"

void agl::Keyboard::linkRenderWindow(agl::RenderWindow window)
{
	this->display = window.getDisplay();
}

// int agl::Keyboard::isKeyPressed(agl::Keyboard::Key key)
// {
// 	char m[32];
// 	XQueryKeymap(this->display, m);
//
// 	for (int i = 0; i < 32; i++)
// 	{
// 		if (m[i] & key)
// 		{
// 			return 1;
// 		}
// 	}
//
// 	return 0;
// }
