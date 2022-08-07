#pragma once

#include "Vector4f.hpp"

namespace agl
{

// Colors
#define red            \
	agl::Vector4f      \
	{                  \
		1., 0., 0., 1. \
	}
#define green          \
	agl::Vector4f      \
	{                  \
		0., 1., 0., 1. \
	}
#define blue           \
	agl::Vector4f      \
	{                  \
		0., 0., 1., 1. \
	}

} // namespace agl
