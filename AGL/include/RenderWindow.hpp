#pragma once

#include "Float2.hpp"
#include "GLPrimative.hpp"
#include "Shader.hpp"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include "Rectangle.hpp"

#include <iostream>

namespace agl
{
	class RenderWindow
	{
		private:
			Display				*dpy;
			Window				 root;
			GLint				 att[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
			XVisualInfo			*vi;
			Colormap			 cmap;
			XSetWindowAttributes swa;
			Window				 win;
			GLXContext			 glc;
			XWindowAttributes	 gwa;

			Atom wmDeleteMessage;

			int		width;
			int		height;
			bool	open;
			int		fpsMilli;
			clock_t lastFrame;

		public:
			/*
			\ Setup the RenderWindow object for drawing onto the screen
			\
			\ int width - The desired width
			\ int height - The desired height
			\ std::string title - The window title
			\ int fps - The target fps for the window
			*/
			void setup(int width, int height, std::string title, int fps);
			void setFPS(int fps);

			void close();

			void clear();
			
			void useShader(Shader shader);
			void drawPrimative(GLPrimative primative);
			void drawShape(Rectangle rectangle);

			void display();

			agl::Float2 pixelToNormalized(agl::Float2 normalized);

			Display *getDisplay()
			{
				return dpy;
			};
			Window getWindow()
			{
				return win;
			}
	};
} // namespace agl
