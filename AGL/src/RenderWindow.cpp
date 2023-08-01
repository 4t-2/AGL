#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>

#include "../include/RenderWindow.hpp"

void agl::RenderWindow::setup(Vec<float, 2> size, const char title[])
{
	agl::createWindow(baseWindow, size, title);

	agl::initGL(baseWindow);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	this->setViewport(0, 0, size.x, size.y);
	this->GLEnable(GL_DEPTH_TEST);
	this->GLEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	agl::mapWindow(baseWindow);

	return;
}

void agl::RenderWindow::setup(std::function<void(agl::RenderWindow &)> f)
{
	f(*this);
}

void agl::RenderWindow::GLEnable(GLenum capability)
{
	glEnable(capability);

	return;
}
void agl::RenderWindow::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);

	return;
}
void agl::RenderWindow::setClearColor(agl::Color color)
{
	Vec<float, 3> colorNormalized = color.normalized();

	glClearColor(colorNormalized.x, colorNormalized.y, colorNormalized.z, 0);

	return;
}

void agl::RenderWindow::setFPS(int fps)
{
	if (!fps)
	{
		fpsMilli = 0;

		sleepFrame = []() {};

		return;
	}
	fpsMilli = 1000 / fps;

	sleepFrame = [&]() {
		timespec ts;

		ts.tv_sec  = fpsMilli / 1000;
		ts.tv_nsec = (fpsMilli % 1000) * 1000000;

		nanosleep(&ts, &ts);
	};

	return;
}

void agl::RenderWindow::setSwapInterval(int i)
{
	agl::setSwapInterval(baseWindow, i);

	return;
}

void agl::RenderWindow::setMvpID(int ID)
{
	mvpID = ID;

	return;
}

void agl::RenderWindow::setTransformID(int ID)
{
	transformID = ID;

	return;
}

void agl::RenderWindow::setShapeColorID(int ID)
{
	shapeColorID = ID;

	return;
}

void agl::RenderWindow::display()
{
	agl::swapBuffers(baseWindow);

	sleepFrame();

	return;
}

void agl::RenderWindow::close()
{
	glDeleteVertexArrays(1, &VertexArrayID); // delete vertex arrays

	closeWindow(baseWindow);

	return;
}

void agl::RenderWindow::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return;
}

void agl::RenderWindow::drawPrimative(agl::GLPrimative primative)
{
	for (int i = 0; i < primative.getBufferAmount(); i++)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, primative.getBuffer(i));
		glVertexAttribPointer(i, primative.getVertexSize(i), GL_FLOAT, GL_FALSE, 0, (void *)0);
	}

	glDrawArrays(primative.getMode(), 0, primative.getVertexAmount());

	for (int i = 0; i < primative.getBufferAmount(); i++)
	{
		glDisableVertexAttribArray(i);
	}

	return;
}

void agl::RenderWindow::drawShape(agl::Shape &shape)
{
	agl::Mat4f transform;
	agl::Mat4f offset	   = shape.getOffsetMatrix();
	agl::Mat4f translation = shape.getTranslationMatrix();
	agl::Mat4f scaling	   = shape.getScalingMatrix();
	agl::Mat4f rotate	   = shape.getRotationMatrix();

	transform = translation * rotate * offset * scaling;

	agl::Mat4f textureTransform;
	agl::Mat4f textureTranslation = shape.getTextureTranslation();
	agl::Mat4f textureScaling	  = shape.getTextureScaling();

	textureTransform = textureTranslation * textureScaling;

	Shader::setUniform(transformID, transform);
	Shader::setUniform(shapeColorID, shape.getColor().normalized());
	Shader::setUniform(textureTransformID, textureTransform);

	Texture::bind(*shape.getTexture());

	this->drawPrimative(shape.getShapeData());

	return;
}

void agl::RenderWindow::drawShape(agl::Shape &shape, std::function<void(RenderWindow &, Shape &)> draw)
{
	draw(*this, shape);
}

void agl::RenderWindow::draw(agl::_Drawable<RenderWindow &> &drawable)
{
	drawable.drawFunction(*this);
}

agl::Vec<float, 2> agl::RenderWindow::drawText(Text &text, float width, Direction align)
{
	agl::Rectangle *shape = text.getCharBox();

	Vec<float, 2> pen;

	if (align == Right)
	{
		pen = {width - (text.getWidth() * text.getScale()), 0};
	}

	Texture::bind(*shape->getTexture());

	for (int i = 0; i < text.getLength(); i++)
	{
		Glyph *glyph = text.getGlyph(i);

		if (glyph->value == '\n' || pen.x + glyph->advance * text.getScale() > width)
		{
			pen.x = 0;
			pen.y += text.getHeight() * text.getScale();
		}

		Vec<float, 3> shapeSize		= {glyph->size.x * text.getScale(), glyph->size.y * text.getScale()};
		Vec<float, 3> shapePosition = {(float)pen.x + (glyph->bearing.x * text.getScale()),
									   (float)pen.y - (glyph->bearing.y * text.getScale()), 0};

		shapePosition.x += (text.getPosition().x);
		shapePosition.y += (text.getPosition().y) + (text.getHeight() * text.getScale());
		shapePosition.z = text.getPosition().z;

		shape->setSize(shapeSize);
		shape->setPosition(shapePosition);
		shape->setTextureScaling(glyph->scale);
		shape->setTextureTranslation(glyph->position);

		agl::Mat4f transform;
		agl::Mat4f translation = shape->getTranslationMatrix();
		agl::Mat4f scaling	   = shape->getScalingMatrix();

		transform = translation * scaling;

		agl::Mat4f textureTransform;
		agl::Mat4f textureTranslation = shape->getTextureTranslation();
		agl::Mat4f textureScaling	  = shape->getTextureScaling();

		textureTransform = textureTranslation * textureScaling;

		Shader::setUniform(transformID, transform);
		Shader::setUniform(shapeColorID, shape->getColor().normalized());
		Shader::setUniform(textureTransformID, textureTransform);

		this->drawPrimative(shape->getShapeData());

		pen.x += glyph->advance * text.getScale();
	}

	return pen;
}

agl::Vec<float, 2> agl::RenderWindow::drawText(agl::Text &text, float width)
{
	return this->drawText(text, width, Left);
}

agl::Vec<float, 2> agl::RenderWindow::drawText(agl::Text &text, Direction align)
{
	return this->drawText(text, INFINITY, align);
}

agl::Vec<float, 2> agl::RenderWindow::drawText(agl::Text &text)
{
	return this->drawText(text, INFINITY, Left);
}


void agl::RenderWindow::setCursorShape(unsigned int shape)
{
	agl::setCursorShape(baseWindow, shape);
}

void agl::RenderWindow::setTextureTransformID(int ID)
{
	textureTransformID = ID;
}

void agl::RenderWindow::getShaderUniforms(Shader shader)
{
	this->setMvpID(shader.getUniformLocation("mvp"));
	this->setTransformID(shader.getUniformLocation("transform"));
	this->setShapeColorID(shader.getUniformLocation("shapeColor"));
	this->setTextureTransformID(shader.getUniformLocation("textureTransform"));

	return;
}

int agl::RenderWindow::getTransformID()
{
	return transformID;
}
int agl::RenderWindow::getShapeColorID()
{
	return shapeColorID;
}
int agl::RenderWindow::getTextureTransformID()
{
	return textureTransformID;
}

void agl::RenderWindow::updateMvp(Camera camera)
{
	agl::Shader::setUniform(mvpID, camera.getMVP());

	return;
}

agl::WindowState agl::RenderWindow::getState()
{
	return agl::getWindowState(baseWindow);
}
