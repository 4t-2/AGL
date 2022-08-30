#include <GL/glew.h>

#include <GL/gl.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/glx.h>

#include <bits/types/struct_timespec.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>

#include "../include/RenderWindow.hpp"

void agl::RenderWindow::setup(int width, int height, std::string title, int fps)
{
	this->width	 = width;
	this->height = height;
	open		 = true;
	this->setFPS(fps);

	dpy = XOpenDisplay(NULL); // tell X to output graphics on computer it was executed

	if (dpy == NULL)
	{
		printf("\n\tcannot connect to X server\n\n");
		exit(0);
	}

	root = DefaultRootWindow(dpy); // root window -- the window that is parent to all others

	vi = glXChooseVisual(dpy, 0,
						 att); // tell OpenGL what it needs to do, stored in att

	if (vi == NULL)
	{
		printf("\n\tno appropriate visual found\n\n");
		exit(0);
	}
	else
	{
		printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone); // create colormap

	swa.colormap   = cmap; // set window attributes
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask,
						&swa); // window is created and the function returns an id

	XMapWindow(dpy, win);				 // make window appear
	XStoreName(dpy, win, title.c_str()); // change the title

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE); // create gl context
	glXMakeCurrent(dpy, win, glc);					// bind it to the window

	glEnable(GL_DEPTH_TEST);

	XGetWindowAttributes(dpy, win, &gwa);
	glViewport(-(gwa.width / 2), -(gwa.width / 2), gwa.width, gwa.height);

	glClearColor(0.5, 0.5, 0.5, 1.0);

	glewInit();

	return;
}

void agl::RenderWindow::setFPS(int fps)
{
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

agl::Float2 agl::RenderWindow::pixelToNormalized(agl::Float2 pixel)
{
	return {pixel.x / gwa.width, pixel.y / gwa.height};
}

agl::Float3 agl::RenderWindow::colorToNormalized(agl::Color color)
{
	return {float(color.r) / 255, float(color.g) / 255, float(color.b) / 255};
}

void agl::RenderWindow::drawShape(agl::Rectangle rectangle)
{
	agl::Float2 size	 = pixelToNormalized(rectangle.getSize());
	agl::Float2 position = pixelToNormalized(rectangle.getPosition());
	agl::Float3 color	 = colorToNormalized(rectangle.getColor());

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
