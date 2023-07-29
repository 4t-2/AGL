#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Cuboid.hpp"
#include "GLPrimative.hpp"
#include "Mat4f.hpp"
#include "Rectangle.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Text.hpp"
#include "Vec.hpp"
#include "Drawable.hpp"

#include "external.hpp"

#include <iostream>
#include <functional>

namespace agl
{
	enum TextAlign
	{
		Left,
		Right
	};

	class RenderWindow
	{
		private:
			int		fpsMilli;
			clock_t lastFrame;

			GLuint VertexArrayID;

			int mvpID;
			int transformID;
			int shapeColorID;
			int textureTransformID;

			std::function<void()> sleepFrame;

		public:
			BaseWindow baseWindow;
			
			// \ Create an AGL Window with defaults that are usable in most projects
			// \ size - the size of the window
			// \ title - the window title
			void setup(Vec<float, 2> size, const char title[]);
			
			void setup(std::function<void(agl::RenderWindow&)> f);

			// Open X displat
			int openDisplay();

			// Create root window
			void createRootWindow();

			// \ Create colormap
			// \ attribute[] - attributes top be used
			// \ alloc - colormap entries to be allocated
			int createColormap(GLint attribute[5], int alloc);

			// \ Set event mask
			// \ eventMask - events
			void setEventMask(long eventMask);

			// \ Create a window with the following parametars
			// \ x - window x position
			// \ y - window y position
			// \ width - window width
			// \ height - window height
			void createWindow(int x, int y, unsigned int width, unsigned int height, unsigned long valueMask);

			// \ Set window title
			// \ title - window title
			void setTitle(std::string title);

			// \ Set window title
			// \ title - window title
			void setTitle(char title[]);

			// \ Map window onto the display
			void mapWindow();

			// \ Initialize OpenGL and GLEW
			void initGL();

			// \ Enable an OpenGL capability
			// \ capability - capability
			void GLEnable(GLenum capability);

			// \ Set the OpenGL viewport
			// \ x - viewport x position
			// \ y - viewport y position
			// \ width - viewport width
			// \ height - viewport height
			void setViewport(int x, int y, int width, int height);

			// \ Set the background color when clearing the screen
			// \ color - background color
			void setClearColor(agl::Color color);

			// \ Set the FPS
			// \ fps = fps
			void setFPS(int fps);

			// \ 0 = disable vsync
			// \ 1 = swap buffer every v blank
			// \ 2 = swap buffer every 2 v blanks
			// \ 3 = etc
			void setSwapInterval(int i);

			// \ Set the uniform location of the MVP
			// \ ID - MVP uniform location
			void setMvpID(int ID);

			// \ Set the uniform location of the Transform uniform
			// \ ID - Transform uniform location
			void setTransformID(int ID);

			// \ Set the uniform location of the Color uniform
			// \ ID - Color uniform location
			void setShapeColorID(int ID);

			// \ Set the uniform location of the textureTransform uniform
			// \ ID - textureTransform uniform location
			void setTextureTransformID(int ID);

			// \ Gets and stores the uniform locations used when rendering an AGL shape
			// \ DO NOT confuse with Shader::use()
			// \ shader - The shader to get uniform locations from
			void getShaderUniforms(Shader shader);

			int getTransformID();
			int getShapeColorID();
			int getTextureTransformID();

			// \ Update the mvp shader uniform according to the chosen camera
			// \ camera - camera to update mvp
			void updateMvp(Camera camera);

			// \ Close the window
			void close();

			// \ Clear the window
			void clear();

			// \ Draw an OpenGL primative onto the window
			// \ primative - OpenGL primative
			void drawPrimative(GLPrimative primative);

			// \ Draw an AGL shape onto the window
			// \ shape - AGL shape
			void drawShape(Shape &shape);

			void drawShape(Shape &shape, std::function<void(RenderWindow&, Shape&)> f);

			void draw(_Drawable<RenderWindow&> &drawable);

			agl::Vec<float, 2> drawText(Text &text);
			agl::Vec<float, 2> drawText(Text &text, float width);
			agl::Vec<float, 2> drawText(Text &text, float width, TextAlign align);
			agl::Vec<float, 2> drawText(Text &text, TextAlign align);

			// \ Swap the display buffer and sleep
			void display();

			void setCursorShape(unsigned int shape);
	};
	
	typedef _Drawable<RenderWindow&> Drawable;
} // namespace agl
