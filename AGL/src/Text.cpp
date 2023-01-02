#include "../include/Text.hpp"

void agl::Text::setFont(Font *font)
{
	this->font = font;
	
	charBox.setTexture(font->getTexture());
	charBox.setColor(agl::Color::White);
}

void agl::Text::setText(char *str, int length)
{
	glyph = new Glyph*[length];
	this->length = length;

	for(int i = 0; i < length; i++)
	{
		glyph[i] = font->getGlyph(str[i]);
	}
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
