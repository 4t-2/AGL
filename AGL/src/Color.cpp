#include "../include/Color.hpp"

const agl::Color agl::Color::Red   = {255, 0, 0, 255};
const agl::Color agl::Color::Green = {0, 255, 0, 255};
const agl::Color agl::Color::Blue  = {0, 0, 255, 255};

const agl::Color agl::Color::Cyan	 = {0, 255, 255, 255};
const agl::Color agl::Color::Magenta = {255, 0, 255, 255};
const agl::Color agl::Color::Yellow	 = {255, 255, 0, 255};

const agl::Color agl::Color::White = {255, 255, 255, 255};
const agl::Color agl::Color::Black = {0, 0, 0, 255};
const agl::Color agl::Color::Gray  = {127, 127, 127, 255};

agl::Vec3f agl::Color::normalized()
{
	return {float(r) / 255, float(g) / 255, float(b) / 255};
}
