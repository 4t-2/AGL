#include <GL/glew.h>

#include <GL/gl.h>
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

	glewInit();

	return;
}

void agl::RenderWindow::setFPS(int fps)
{
	fpsMilli = 1000 / fps;

	return;
}

int agl::RenderWindow::getEvent()
{
	XNextEvent(this->dpy, &this->xev);

	return xev.type;
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

	open = false;

	return;
}

void agl::RenderWindow::clear()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return;
}

void agl::RenderWindow::draw(agl::GLTriangle triangle)
{
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.getVertexBuffer());

	glVertexAttribPointer(0,		// attribute 0. No particular reason for 0, but
									// must match the layout in the shader.
						  3,		// size
						  GL_FLOAT, // type
						  GL_FALSE, // normalized?
						  0,		// stride
						  (void *)0 // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0,
				 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

	return;
}

void agl::RenderWindow::draw(agl::RectangleShape rectangle)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);

	glColor3f(1., 0., 0.); // bottom left
	Vector2f bl;
	bl.x = rectangle.getPosition().x;
	bl.x /= width / 2.;
	bl.x -= 1;
	bl.y = rectangle.getPosition().y;
	bl.y /= height / 2.;
	bl.y -= 1;
	glVertex3f(bl.x, bl.y, 0.);

	glColor3f(0., 1., 0.); // bottom right
	Vector2f br;
	br.x = rectangle.getPosition().x + rectangle.getSize().x;
	br.x /= width / 2.;
	br.x -= 1;
	br.y = rectangle.getPosition().y;
	br.y /= height / 2.;
	br.y -= 1;
	glVertex3f(br.x, br.y, 0.);

	glColor3f(0., 0., 1.); // top right
	Vector2f tr;
	tr.x = rectangle.getPosition().x + rectangle.getSize().x;
	tr.x /= width / 2.;
	tr.x -= 1;
	tr.y = rectangle.getPosition().y + rectangle.getSize().y;
	tr.y /= height / 2.;
	tr.y -= 1;
	glVertex3f(tr.x, tr.y, 0.);

	glColor3f(1., 1., 0.); // top left
	Vector2f tl;
	tl.x = rectangle.getPosition().x;
	tl.x /= width / 2.;
	tl.x -= 1;
	tl.y = rectangle.getPosition().y + rectangle.getSize().y;
	tl.y /= height / 2.;
	tl.y -= 1;
	glVertex3f(tl.x, tl.y, 0.);

	glEnd();

	return;
}

void agl::RenderWindow::draw(agl::GLPrimative primative)
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

	// Draw the triangle !
	glDrawArrays(primative.getMode(), 0,
				 primative.getVertices()); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

	return;
}

bool agl::RenderWindow::isOpen()
{
	return open;
}
