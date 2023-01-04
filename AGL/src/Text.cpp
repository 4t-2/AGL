#include "../include/Text.hpp"

void agl::Text::setFont(Font *font)
{
	this->font = font;
	this->height = font->getHeight();

	charBox.setTexture(font->getTexture());
	charBox.setColor(agl::Color::White);
}

void agl::Text::setText(std::string str)
{
	length = str.length();
	glyph = new Glyph*[length];

	for(int i = 0; i < length; i++)
	{
		glyph[i] = font->getGlyph(str[i]);
	}
}

void agl::Text::setScale(float scale)
{
	this->scale = scale;
}

void agl::Text::setPosition(agl::Vec<float, 3> position)
{
	this->position = position;
}

void agl::Text::setColor(agl::Color color)
{
	charBox.setColor(color);
}

void agl::Text::clearText()
{
	delete[] glyph;
}

agl::Glyph *agl::Text::getGlyph(int i)
{
	return glyph[i];
}

agl::Rectangle *agl::Text::getCharBox()
{
	return &charBox;
}

int agl::Text::getLength()
{
	return length;
}

agl::Font* agl::Text::getFont()
{
	return font;
}

int agl::Text::getHeight()
{
	return height;
}

agl::Vec<float, 3> agl::Text::getPosition()
{
	return position;
}

float agl::Text::getScale()
{
	return scale;
}
