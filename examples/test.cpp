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
	agl::Vec3f rotation = {0, 0, 0};

	agl::Cuboid cuboid;
	cuboid.setSize({1, 1, 1});
	cuboid.setPosition(position);
	cuboid.setColor(agl::Color::Blue);

	agl::Circle circle(100);
	circle.setSize(size);
	circle.setPosition(position);
	circle.setColor(agl::Color::Red);

	agl::Rectangle rectangle;
	rectangle.setSize({1, 1, 1});
	rectangle.setPosition(position);
	rectangle.setColor(agl::Color::Blue);

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
		
		window.drawShape(rectangle);

		window.display();

		if(event.isKeyPressed(XK_q))
		{
			rotation.x++;
		} else if(event.isKeyPressed(XK_w))
		{
			rotation.x--;
		}

		if(event.isKeyPressed(XK_a))
		{
			rotation.y++;
		} else if(event.isKeyPressed(XK_s))
		{
			rotation.y--;
		}

		if(event.isKeyPressed(XK_z))
		{
			rotation.z++;
		} else if(event.isKeyPressed(XK_x))
		{
			rotation.z--;
		}

		rectangle.setSize(size);
		rectangle.setPosition(position);
		rectangle.setRotation(rotation);
	}
	
	shader.deleteProgram();

	window.close();

	return 0;
}
