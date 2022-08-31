#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Rectangle.hpp"
#include "Shader.hpp"
#include "Vec2f.hpp"
#include "Vec2i.hpp"
#include "Vec3f.hpp"
#include <GL/glx.h>
#include <X11/Xlib.h>

#include <iostream>

namespace agl
{
	class RenderWindow
	{
		private:
			Display		*dpy;
			Window		 root;
			XVisualInfo *vi;
			Colormap	 cmap;
			long		 eventMask;
			Window		 win;
			GLXContext	 glc;
			
			Atom wmDeleteMessage;

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

			void setup2D(int width, int height, std::string title, int fps, agl::Color clearColor);

			int	 openDisplay();
			void createRootWindow();
			int	 createColormap(GLint attribute[5], int alloc);
			void setEventMask(long eventMask);
			void createWindow(int x, int y, unsigned int width, unsigned int height, unsigned long valueMask);
			void setTitle(std::string title);
			void setTitle(char title[]);
			void mapWindow();
			void initGL();
			void GLEnable(GLenum capability);
			void setViewport(int x, int y, int width, int height);
			void setClearColor(agl::Color color);
			void setFPS(int fps);

			void close();

			void clear();

			void useShader(Shader shader);
			void drawPrimative(GLPrimative primative);
			void drawShape(Rectangle rectangle);

			void display();

			agl::Vec2f pixelToNormalized(agl::Vec2f pixel);
			agl::Vec3f colorToNormalized(agl::Color color);

			XWindowAttributes getWindowAttributes();

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
