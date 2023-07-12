#pragma once

#include "Vec.hpp"
#include "BaseWindow.hpp"

namespace agl
{

void createWindow(BaseWindow &window, agl::Vec<int, 2> position, agl::Vec<int, 2> size, std::string title);
void initGL(BaseWindow &window);
void mapWindow(BaseWindow &window);
void pollEvents(BaseWindow window);
}