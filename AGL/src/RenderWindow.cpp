#include <GL/glew.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <bits/types/struct_timespec.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>

#include "../include/RenderWindow.hpp"

void agl::RenderWindow::setup2D(int width, int height, std::string title, int fps, agl::Color clearColor)
{
	GLint attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	this->openDisplay();
	this->createRootWindow();
	this->createColormap(attribute, AllocNone);
	this->setEventMask(ExposureMask | KeyPressMask);
	this->createWindow(0, 0, width, height, CWColormap | CWEventMask);
	this->setTitle(title);
	
	XWindowAttributes gwa = this->getWindowAttributes();

	this->initGL();
	this->setViewport(0, 0, gwa.width, gwa.height);
	this->setClearColor(clearColor);
	this->setFPS(fps);
	this->mapWindow();

	return;
}

int agl::RenderWindow::openDisplay()
{
	dpy = XOpenDisplay(NULL);

	if (dpy == NULL)
	{
		return 1;
	}

	return 0;
}

void agl::RenderWindow::createRootWindow()
{
	root = DefaultRootWindow(dpy);

	return;
}

int agl::RenderWindow::createColormap(GLint attribute[5], int alloc)
{
	vi = glXChooseVisual(dpy, 0, attribute);

	if (vi == NULL)
	{
		return 1;
	}

	cmap = XCreateColormap(dpy, root, vi->visual, alloc);

	return 0;
}

void agl::RenderWindow::setEventMask(long eventMask)
{
	this->eventMask = eventMask;

	return;
}

void agl::RenderWindow::createWindow(int x, int y, unsigned int width, unsigned int height, unsigned long valueMask)
{
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask = eventMask;

	win = XCreateWindow(dpy, root, x, y, width, height, 0, vi->depth, InputOutput, vi->visual, valueMask,
						&swa); // window is created and the function returns an id

	return;
}
void agl::RenderWindow::setTitle(std::string title)
{
	XStoreName(dpy, win, title.c_str());

	return;
}
void agl::RenderWindow::setTitle(char title[])
{
	XStoreName(dpy, win, title);

	return;
}
void agl::RenderWindow::mapWindow()
{
	XMapWindow(dpy, win);

	return;
}
void agl::RenderWindow::initGL()
{
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc); // bind it to the window
	glewInit();

	return;
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
	Vec3f colorNormalized = colorToNormalized(color);

	glClearColor(colorNormalized.x, colorNormalized.y, colorNormalized.z, 0);

	return;
}

void agl::RenderWindow::setFPS(int fps)
{
	if (!fps)
	{
		fpsMilli = 0;
		return;
	}
	fpsMilli = 1000 / fps;

	return;
}

void agl::RenderWindow::display()
{
	glXSwapBuffers(this->dpy, this->win);

	struct timespec ts;

	ts.tv_sec  = fpsMilli / 1000;
	ts.tv_nsec = (fpsMilli % 1000) * 1000000;

	nanosleep(&ts, &ts);

	return;
}

void agl::RenderWindow::close()
{
	glXMakeCurrent(dpy, None, NULL); // release gl binding to window
	glXDestroyContext(dpy, glc);	 // destroy context
	XDestroyWindow(dpy, win);		 // kill window
	XCloseDisplay(dpy);				 // close display

	return;
}

void agl::RenderWindow::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return;
}

void agl::RenderWindow::useShader(agl::Shader shader)
{
	glUseProgram(shader.getProgramID());

	return;
}

void agl::RenderWindow::drawPrimative(agl::GLPrimative primative)
{
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, primative.getVertexBuffer());

	glVertexAttribPointer(0,		// attribute 0. No particular reason for 0, but
									// must match the layout in the shader.
						  3,		// size
						  GL_FLOAT, // type
						  GL_FALSE, // normalized?
						  0,		// stride
						  (void *)0 // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, primative.getColorBuffer());
	glVertexAttribPointer(1,		// attribute. No particular reason for 1, but must
									// match the layout in the shader.
						  3,		// size
						  GL_FLOAT, // type
						  GL_FALSE, // normalized?
						  0,		// stride
						  (void *)0 // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(primative.getMode(), 0,
				 primative.getVertexDataSize() / 12); // Starting from vertex 0; 3 vertices
													  // total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	return;
}

agl::Vec2f agl::RenderWindow::pixelToNormalized(agl::Vec2f pixel)
{
	XWindowAttributes gwa = this->getWindowAttributes();
	return {pixel.x / gwa.width, pixel.y / gwa.height};
}

agl::Vec3f agl::RenderWindow::colorToNormalized(agl::Color color)
{
	return {float(color.r) / 255, float(color.g) / 255, float(color.b) / 255};
}

void agl::RenderWindow::drawShape(agl::Rectangle rectangle)
{
	agl::Vec2f size		= pixelToNormalized(rectangle.getSize());
	agl::Vec2f position = pixelToNormalized(rectangle.getPosition());
	agl::Vec3f color	= colorToNormalized(rectangle.getColor());

	float vertexData[12] = {
		position.x,			 position.y,		  0, // 1
		position.x + size.x, position.y,		  0, // 2
		position.x,			 position.y + size.y, 0, // 3
		position.x + size.x, position.y + size.y, 0, // 4
	};

	float colorData[12] = {
		color.x, color.y, color.z, // 1
		color.x, color.y, color.z, // 2
		color.x, color.y, color.z, // 3
		color.x, color.y, color.z, // 4
	};

	agl::GLPrimative shape;

	shape.setMode(GL_TRIANGLE_STRIP);
	shape.setVertexData(vertexData, sizeof(vertexData));
	shape.setColorData(colorData, sizeof(colorData));

	this->drawPrimative(shape);

	return;
}

XWindowAttributes agl::RenderWindow::getWindowAttributes()
{
	XWindowAttributes gwa;
	XGetWindowAttributes(dpy, win, &gwa);

	return gwa;
}
