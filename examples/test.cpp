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

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, -1.0f, // triangle 1 vertex 1
		-1.0f, -1.0f, 1.0f,	 // triangle 1 vertex 2
		-1.0f, 1.0f,  1.0f,	 // triangle 1 vertex 3
		1.0f,  1.0f,  -1.0f, // triangle 2 vertex 1
		-1.0f, -1.0f, -1.0f, // triangle 2 vertex 2
		-1.0f, 1.0f,  -1.0f, // triangle 2 vertex 3
		1.0f,  -1.0f, 1.0f,	 // triangle 3 vertex 1
		-1.0f, -1.0f, -1.0f, // triangle 3 vertex 2
		1.0f,  -1.0f, -1.0f, // triangle 3 vertex 3
		1.0f,  1.0f,  -1.0f, // triangle 4 vertex 1
		1.0f,  -1.0f, -1.0f, // triangle 4 vertex 2
		-1.0f, -1.0f, -1.0f, // triangle 4 vertex 3
		-1.0f, -1.0f, -1.0f, // triangle 5 vertex 1
		-1.0f, 1.0f,  1.0f,	 // triangle 5 vertex 2
		-1.0f, 1.0f,  -1.0f, // triangle 5 vertex 3
		1.0f,  -1.0f, 1.0f,	 // triangle 6 vertex 1
		-1.0f, -1.0f, 1.0f,	 // triangle 6 vertex 2
		-1.0f, -1.0f, -1.0f, // triangle 6 vertex 3
		-1.0f, 1.0f,  1.0f,	 // triangle 7 vertex 1
		-1.0f, -1.0f, 1.0f,	 // triangle 7 vertex 2
		1.0f,  -1.0f, 1.0f,	 // triangle 7 vertex 3
		1.0f,  1.0f,  1.0f,	 // triangle 8 vertex 1
		1.0f,  -1.0f, -1.0f, // triangle 8 vertex 2
		1.0f,  1.0f,  -1.0f, // triangle 8 vertex 3
		1.0f,  -1.0f, -1.0f, // triangle 9 vertex 1
		1.0f,  1.0f,  1.0f,	 // triangle 9 vertex 2
		1.0f,  -1.0f, 1.0f,	 // triangle 9 vertex 3
		1.0f,  1.0f,  1.0f,	 // triangle 10 vertex 1
		1.0f,  1.0f,  -1.0f, // triangle 10 vertex 2
		-1.0f, 1.0f,  -1.0f, // triangle 10 vertex 3
		1.0f,  1.0f,  1.0f,	 // triangle 11 vertex 1
		-1.0f, 1.0f,  -1.0f, // triangle 11 vertex 2
		-1.0f, 1.0f,  1.0f,	 // triangle 11 vertex 3
		1.0f,  1.0f,  1.0f,	 // triangle 12 vertex 1
		-1.0f, 1.0f,  1.0f,	 // triangle 12 vertex 2
		1.0f,  -1.0f, 1.0f	 // triangle 12 vertex 3
	};

	GLfloat g_color_buffer_data[] = {
		0.583f, 0.771f, 0.014f, // triangle 1 vertex 1
		0.609f, 0.115f, 0.436f, // triangle 1 vertex 2
		0.327f, 0.483f, 0.844f, // triangle 1 vertex 3
		0.822f, 0.569f, 0.201f, // triangle 2 vertex 1
		0.435f, 0.602f, 0.223f, // triangle 2 vertex 2
		0.310f, 0.747f, 0.185f, // triangle 2 vertex 3
		0.597f, 0.770f, 0.761f, // triangle 3 vertex 1
		0.559f, 0.436f, 0.730f, // triangle 3 vertex 2
		0.359f, 0.583f, 0.152f, // triangle 3 vertex 3
		0.483f, 0.596f, 0.789f, // triangle 4 vertex 1
		0.559f, 0.861f, 0.639f, // triangle 4 vertex 2
		0.195f, 0.548f, 0.859f, // triangle 4 vertex 3
		0.014f, 0.184f, 0.576f, // triangle 5 vertex 1
		0.771f, 0.328f, 0.970f, // triangle 5 vertex 2
		0.406f, 0.615f, 0.116f, // triangle 5 vertex 3
		0.676f, 0.977f, 0.133f, // triangle 6 vertex 1
		0.971f, 0.572f, 0.833f, // triangle 6 vertex 2
		0.140f, 0.616f, 0.489f, // triangle 6 vertex 3
		0.997f, 0.513f, 0.064f, // triangle 7 vertex 1
		0.945f, 0.719f, 0.592f, // triangle 7 vertex 2
		0.543f, 0.021f, 0.978f, // triangle 7 vertex 3
		0.279f, 0.317f, 0.505f, // triangle 8 vertex 1
		0.167f, 0.620f, 0.077f, // triangle 8 vertex 2
		0.347f, 0.857f, 0.137f, // triangle 8 vertex 3
		0.055f, 0.953f, 0.042f, // triangle 9 vertex 1
		0.714f, 0.505f, 0.345f, // triangle 9 vertex 2
		0.783f, 0.290f, 0.734f, // triangle 9 vertex 3
		0.722f, 0.645f, 0.174f, // triangle 10 vertex 1
		0.302f, 0.455f, 0.848f, // triangle 10 vertex 2
		0.225f, 0.587f, 0.040f, // triangle 10 vertex 3
		0.517f, 0.713f, 0.338f, // triangle 11 vertex 1
		0.053f, 0.959f, 0.120f, // triangle 11 vertex 2
		0.393f, 0.621f, 0.362f, // triangle 11 vertex 3
		0.673f, 0.211f, 0.457f, // triangle 12 vertex 1
		0.820f, 0.883f, 0.371f, // triangle 12 vertex 2
		0.982f, 0.099f, 0.879f	// triangle 12 vertex 3
	};

	agl::GLPrimative cube;
	cube.setMode(GL_TRIANGLES);
	cube.setVertexData(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	cube.setColorData(g_color_buffer_data, sizeof(g_color_buffer_data));

	float triangle_vertData[] = {
		0.0,  0.5,	0.0, // 1
		0.5,  -0.5, 0.0, // 1
		-0.5, -0.5, 0.0, // 1
	};

	float triangle_colorData[] = {
		1, 0, 0, // 1
		0, 1, 0, // 1
		0, 0, 1, // 1
	};

	agl::GLPrimative triangle;
	triangle.setMode(GL_TRIANGLES);
	triangle.setColorData(triangle_colorData, sizeof(triangle_colorData));
	triangle.setVertexData(triangle_vertData, sizeof(triangle_vertData));

	agl::Camera camera;
	camera.setPerspectiveProjection(45, (float)WIDTH / (float)HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	shader.setCamera(camera);
	shader.use();
	shader.updateCamera(camera);

	agl::Vec2i offset;

	agl::Vec3f pos = {4, 3, 3};

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawPrimative(cube);

		window.display();
	}

	window.close();

	shader.remove();

	return 0;
}
