#include "../AGL/agl.hpp"

#define TITLE  "winfloat"
#define WIDTH  500
#define HEIGHT 500
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

	agl::Vec3f pos = {0, 0, 0};

	agl::Cuboid cuboid;
	cuboid.setSizePosition({1, 1, 1}, pos);
	cuboid.setColor(agl::Color::Blue);

	agl::Rectangle rectangle;
	rectangle.setSizePosition({1, 1}, {pos.x, pos.y});
	rectangle.setColor(agl::Color::Red);

	agl::Camera camera;
	camera.setPerspectiveProjection(45, (float)WIDTH / (float)HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	shader.setCamera(camera);
	shader.use();
	shader.updateCamera(camera);

	agl::Vec2i offset;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		if (!event.isKeyPressed(XK_space))
		{
			window.drawShape(cuboid);
		}
		else
		{
			window.drawShape(rectangle);
		}

		window.display();

		if (event.isKeyPressed(XK_Up))
		{
			pos.y += 0.01;
		}
		if (event.isKeyPressed(XK_Down))
		{
			pos.y -= 0.01;
		}
		if (event.isKeyPressed(XK_Left))
		{
			pos.x -= 0.01;
		}
		if (event.isKeyPressed(XK_Right))
		{
			pos.x += 0.01;
		}

		cuboid.setSizePosition({1, 1, 1}, pos);
		rectangle.setSizePosition({1, 1}, {pos.x, pos.y});
	}

	window.close();

	shader.deleteProgram();

	cuboid.deleteData();
	rectangle.deleteData();

	return 0;
}
