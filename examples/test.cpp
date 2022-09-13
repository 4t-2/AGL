#include "../AGL/agl.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>

#define TITLE  "winfloat"
#define WIDTH  500.
#define HEIGHT 500.
#define FPS	   60
#define CLEARCOLOR         \
	{                      \
		127, 127, 127, 127 \
	}

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	GLint			  attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	window.openDisplay();
	window.createRootWindow();
	window.createColormap(attribute, AllocNone);
	window.setEventMask(ExposureMask | KeyPressMask);
	window.createWindow(0, 0, WIDTH, HEIGHT, CWColormap | CWEventMask);
	window.setTitle(TITLE);

	XWindowAttributes gwa = window.getWindowAttributes();

	window.initGL();
	window.setViewport(0, 0, gwa.width, gwa.height);
	window.setClearColor(CLEARCOLOR);
	window.setFPS(FPS);
	window.mapWindow();

	window.GLEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("./vert.vert", "./frag.frag");

	agl::Vec3f size		= {1, 1, 1};
	agl::Vec3f position = {0, 0, 0};

	agl::Cuboid cuboid;
	cuboid.setSize({1, 1, 1});
	cuboid.setPosition(size);
	cuboid.setColor(agl::Color::Blue);

	agl::Camera camera;
	camera.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	shader.setCamera(camera);
	shader.use();
	shader.updateCamera();

	agl::Vec2i offset;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();
		
		window.drawShape(cuboid);

		window.display();

		if (event.isKeyPressed(XK_Shift_L))
		{
			if (event.isKeyPressed(XK_Up))
			{
				size.z -= 0.01;
			}
			if (event.isKeyPressed(XK_Down))
			{
				size.z += 0.01;
			}
			if (event.isKeyPressed(XK_Left))
			{
				size.x += 0.01;
			}
			if (event.isKeyPressed(XK_Right))
			{
				size.x -= 0.01;
			}

			if (event.isKeyPressed(XK_q))
			{
				size.y -= 0.01;
			}
			if (event.isKeyPressed(XK_e))
			{
				size.y += 0.01;
			}
		}
		else
		{
			if (event.isKeyPressed(XK_Up))
			{
				position.z -= 0.01;
			}
			if (event.isKeyPressed(XK_Down))
			{
				position.z += 0.01;
			}
			if (event.isKeyPressed(XK_Left))
			{
				position.x += 0.01;
			}
			if (event.isKeyPressed(XK_Right))
			{
				position.x -= 0.01;
			}

			if (event.isKeyPressed(XK_q))
			{
				position.y -= 0.01;
			}
			if (event.isKeyPressed(XK_e))
			{
				position.y += 0.01;
			}
		}

		cuboid.setSize(size);
		cuboid.setPosition(position);
	}
	
	shader.deleteProgram();

	window.close();

	return 0;
}
