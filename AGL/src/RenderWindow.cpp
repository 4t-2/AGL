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

void agl::RenderWindow::setup(Vec<float, 2> size, const char title[])
{
	GLint attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	this->openDisplay();
	this->createRootWindow();
	this->createColormap(attribute, AllocNone);
	this->setEventMask(ExposureMask | KeyPressMask);
	this->createWindow(0, 0, size.x, size.y, CWColormap | CWEventMask);
	this->setTitle(title);

	XWindowAttributes gwa = this->getWindowAttributes();

	this->initGL();
	this->setViewport(0, 0, gwa.width, gwa.height);
	this->GLEnable(GL_DEPTH_TEST);

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
	swa.colormap   = cmap;
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

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

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
	Vec<float, 3> colorNormalized = color.normalized();

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
	glXSwapBuffers(this->dpy, this->win);

	struct timespec ts;

	ts.tv_sec  = fpsMilli / 1000;
	ts.tv_nsec = (fpsMilli % 1000) * 1000000;

	nanosleep(&ts, &ts);

	return;
}

void agl::RenderWindow::close()
{
	glDeleteVertexArrays(1, &VertexArrayID);

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
	agl::Mat4f offset = shape.getOffsetMatrix();
	agl::Mat4f translation = shape.getTranslationMatrix();
	agl::Mat4f scaling = shape.getScalingMatrix();
	agl::Mat4f rotate = shape.getRotationMatrix();

	transform = translation * rotate * offset * scaling;

	Shader::setUniformMatrix4fv(transformID, transform);
	Shader::setUniformVector3fv(shapeColorID, shape.getColor().normalized());

	Texture::bind(shape.getTextureID());

	this->drawPrimative(shape.getShapeData());

	Texture::bind(0);

	return;
}

XWindowAttributes agl::RenderWindow::getWindowAttributes()
{
	XWindowAttributes gwa;
	XGetWindowAttributes(dpy, win, &gwa);

	return gwa;
}

void agl::RenderWindow::getShaderUniforms(Shader shader)
{
	this->setMvpID(shader.getUniformLocation("mvp"));
	this->setTransformID(shader.getUniformLocation("transform"));
	this->setShapeColorID(shader.getUniformLocation("shapeColor"));

	return;
}

void agl::RenderWindow::updateMvp(Camera camera)
{
	agl::Shader::setUniformMatrix4fv(mvpID, camera.getMVP());

	return;
}
