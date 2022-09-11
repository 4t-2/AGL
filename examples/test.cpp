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

	agl::Vec3f pos = {0, 0, 5};

	agl::Cuboid cuboid;
	cuboid.setSize({1, 1, 1});
	cuboid.setPosition(pos);
	cuboid.setColor(agl::Color::Blue);
	cuboid.setData();

	agl::Rectangle rectangle;
	rectangle.setColor(agl::Color::Red);

	agl::Circle circle(88);

	agl::Camera camera;
	// camera.setPerspectiveProjection(45, (float)WIDTH / (float)HEIGHT, 0, 100);
	camera.setView(pos, {0, 0, 0}, {0, 1, 0});

	camera.setOrthographicProjection(-1, 1, -1, 1, 0, 100);

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

		window.drawShape(cuboid);

		window.display();

		if (event.isKeyPressed(XK_Up))
		{
			pos.z -= 0.01;
		}
		if (event.isKeyPressed(XK_Down))
		{
			pos.z += 0.01;
		}
		if (event.isKeyPressed(XK_Left))
		{
			pos.x += 0.01;
		}
		if (event.isKeyPressed(XK_Right))
		{
			pos.x -= 0.01;
		}

		if(event.isKeyPressed(XK_q))
		{
			pos.y -= 0.01;
		} if(event.isKeyPressed(XK_e))
		{
			pos.y += 0.01;
		}

		printf("%f %f %f\n", pos.x, pos.y, pos.z);

		camera.setView(pos, {0, 0, 0}, {0, 1, 0});
		shader.updateCamera(camera);
	}

	shader.deleteProgram();

	window.close();

	return 0;
}
