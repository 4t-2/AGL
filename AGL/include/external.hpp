#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include "crossplatform.hpp"

#ifdef _WIN32
#define AGL_STB_TRUETYPE_INC "stb_truetype.h"
#define AGL_STB_IMAGE_INC "stb_image.h"
#endif

#ifdef __linux__
#define AGL_STB_TRUETYPE_INC <stb/stb_truetype.h>
#define AGL_STB_IMAGE_INC <stb/stb_image.h>
#endif
