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

#include "../include/Macros.hpp"

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
	glViewport(0, 0, gwa.width, gwa.height);

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

bool agl::RenderWindow::isKeyPressed(int keysym)
{
	char keymap[32];
	XQueryKeymap(dpy, keymap);

	int keycode = XKeysymToKeycode(dpy, keysym);

	if (keymap[keycode / 8] & (0x1 << (keycode % 8)))
	{

		return true;
	}

	return false;
}

agl::Vector2i agl::RenderWindow::getPointerPosition()
{
	Window		 rootReturn, childReturn;
	int			 rootx, rooty;
	int			 winx, winy;
	unsigned int maskReturn;
	XQueryPointer(dpy, win, &rootReturn, &childReturn, &rootx, &rooty, &winx, &winy, &maskReturn);
	printf("%d\n", maskReturn);
	return {winx, winy};
}
