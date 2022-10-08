#include "../AGL/agl.hpp"
#include "../AGL/include/Mat4f.hpp"

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

	agl::Shader shader1;
	agl::Shader shader2;
	shader1.loadFromFile("./vert1.vert", "./frag1.frag");
	shader2.loadFromFile("./vert.vert", "./frag.frag");

	agl::Camera camera1;
	camera1.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera1.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	agl::Camera camera2;
	camera2.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera2.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	agl::Texture UVTexture1;
	agl::Texture UVtexture2;
	UVTexture1.loadFromFile("./uvtemplate.bmp");
	UVtexture2.loadFromFile("./uvtemplateInvert.bmp");

	agl::Cuboid cuboid;
	cuboid.setTexture(&UVTexture1);

	int transformID1 = shader1.getUniformLocation("Transform");
	int vecID1		 = shader1.getUniformLocation("vec3Color");
	camera1.setMvpID(shader1.getUniformLocation("MVP"));

	int transformID2 = shader2.getUniformLocation("Transform");
	camera2.setMvpID(shader2.getUniformLocation("MVP"));

	agl::Vec3f pos = {4, 3, 3};

	float x = 0;

	while (!event.windowClose())
	{
		x += 0.01;
		if (x >= 1)
		{
			x = 0;
		}

		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		if (event.isKeyPressed(XK_Return))
		{
			shader1.use();
			window.setTransformID(shader1.getUniformLocation("Transform"));
			camera1.update();
			agl::Shader::setUniformVector3fv(vecID1, {0, 0, x});
		}
		else
		{
			shader2.use();
			window.setTransformID(shader2.getUniformLocation("Transform"));
			camera2.update();
		}

		window.clear();

		window.drawShape(cuboid);

		window.display();

		static float speed = 0.01;

		if (event.isKeyPressed(XK_Left))
		{
			pos.x -= speed;
		}
		if (event.isKeyPressed(XK_Right))
		{
			pos.x += speed;
		}
		if (event.isKeyPressed(XK_space))
		{
			pos.y += speed;
		}
		if (event.isKeyPressed(XK_Control_L))
		{
			pos.y -= speed;
		}
		if (event.isKeyPressed(XK_Up))
		{
			pos.z -= speed;
		}
		if (event.isKeyPressed(XK_Down))
		{
			pos.z += speed;
		}

		camera1.setView(pos, {0, 0, 0}, {0, 1, 0});
		camera2.setView({-pos.x, -pos.y, -pos.z}, {0, 0, 0}, {0, 1, 0});
	}

	shader1.deleteProgram();

	UVTexture1.deleteTexture();

	window.close();

	return 0;
}
