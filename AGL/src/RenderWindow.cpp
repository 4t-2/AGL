#include <GL/glew.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <bits/types/struct_timespec.h>
#include <cstdlib>
#include <ctime>
#include <glm/ext/matrix_float4x4.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>

#include "../include/RenderWindow.hpp"

void agl::RenderWindow::setup2D(int width, int height, std::string title, int fps, agl::Color clearColor,
								glm::mat4 *MPV)
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

	*MPV = glm::ortho(float(0), float(width), float(height), float(0));

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
	Vec3f colorNormalized = color.normalized();

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
				 primative.getBufferSize() / 12); // Starting from vertex 0; 3
												  // vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	return;
}

namespace matFuncs
{

	void translate(glm::mat4 &mat, agl::Vec3f position)
	{
		mat[3][3] = 1.0f;

		mat[0][0] = 1.0f;
		mat[1][1] = 1.0f;
		mat[2][2] = 1.0f;

		mat[3][0] = position.x;
		mat[3][1] = position.y;
		mat[3][2] = position.z;

		return;
	}

	void scale(glm::mat4 &mat, agl::Vec3f size)
	{
		mat[3][3] = 1.0f;

		mat[0][0] = size.x;
		mat[1][1] = size.y;
		mat[2][2] = size.z;

		return;
	}

	void rotateX(glm::mat4 &mat, float x)
	{
		mat[3][3] = 1.0f;
		mat[0][0] = 1.0f;

		float xSin = sin(x * 3.14 / 180);
		float xCos = cos(x * 3.14 / 180);

		mat[1][1] = xCos;
		mat[2][2] = xCos;
		mat[1][2] = xSin;
		mat[2][1] = -xSin;

		return;
	}

	void rotateY(glm::mat4 &mat, float y)
	{
		mat[1][1] = 1.0f;
		mat[3][3] = 1.0f;

		float ySin = sin(y * 3.14 / 180);
		float yCos = cos(y * 3.14 / 180);

		mat[0][0] = yCos;
		mat[2][2] = yCos;
		mat[0][2] = ySin;
		mat[2][0] = -ySin;

		return;
	}

	void rotateZ(glm::mat4 &mat, float z)
	{
		mat[2][2] = 1.0f;
		mat[3][3] = 1.0f;

		float zSin = sin(z * 3.14 / 180);
		float zCos = cos(z * 3.14 / 180);

		mat[0][0] = zCos;
		mat[1][1] = zCos;
		mat[1][0] = zSin;
		mat[0][1] = -zSin;

		return;
	}

} // namespace matFuncs

void agl::RenderWindow::drawShape(agl::Shape &shape, Shader shader, int transformID)
{
	// shape.setShapeData();
	
	glm::mat4 transform;
	glm::mat4 translate = glm::mat4();
	glm::mat4 scale		= glm::mat4();
	glm::mat4 rotation	= glm::mat4();
	glm::mat4 rotationX = glm::mat4();
	glm::mat4 rotationY = glm::mat4();
	glm::mat4 rotationZ = glm::mat4();

	matFuncs::translate(translate, shape.getPosition());
	matFuncs::scale(scale, shape.getSize());
	matFuncs::rotateX(rotationX, shape.getRotation().x);
	matFuncs::rotateY(rotationY, shape.getRotation().y);
	matFuncs::rotateZ(rotationZ, shape.getRotation().z);

	rotation  = rotationX * rotationY * rotationZ;
	transform = translate * rotation * scale;

	shader.setUniformMatrix4fv(transformID, &transform[0][0]);

	this->drawPrimative(shape.getShapeData());

	return;
}

XWindowAttributes agl::RenderWindow::getWindowAttributes()
{
	XWindowAttributes gwa;
	XGetWindowAttributes(dpy, win, &gwa);

	return gwa;
}
