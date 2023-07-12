#pragma once

#include <gl/gl.h>
#include <gl/glew.h>
#include "crossfunctions.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#endif