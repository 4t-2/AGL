#pragma once

#include "Color.hpp"
#include "Cuboid.hpp"
#include "GLPrimative.hpp"
#include "Rectangle.hpp"
#include "Shader.hpp"
#include "Vec2f.hpp"
#include "Vec2i.hpp"
#include "Vec3f.hpp"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <glm/gtc/matrix_transform.hpp>

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
			void setup2D(int width, int height, std::string title, int fps, agl::Color clearColor, glm::mat4 *MPV);

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

			void drawPrimative(GLPrimative primative);
			void drawShape(Rectangle rectangle);
			void drawShape(Cuboid cuboid);

			void display();

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
