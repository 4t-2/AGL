#include "../../../AGL/agl.hpp"

int main()
{
	agl::RenderWindow window;
	agl::Event		  event;
	agl::Shader		  shader;
	agl::GLPrimative  triangle;

	// setup window

	GLint attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	window.openDisplay();
	window.createRootWindow();
	window.createColormap(attribute, AllocNone);
	window.setEventMask(ExposureMask | KeyPressMask);
	window.createWindow(0, 0, 1000, 1000, CWColormap | CWEventMask);
	window.setTitle("Triangle");

	XWindowAttributes gwa = window.getWindowAttributes();

	window.initGL();
	window.setViewport(0, 0, gwa.width, gwa.height);
	window.setClearColor(agl::Color::Black);
	window.setFPS(60);
	window.mapWindow();

	window.GLEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// enable events

	event.setWindow(window);

	// load and use the shaders

	shader.loadFromFile("./vert.vert", "./frag.frag");
	shader.use();

	// set the vertex and buffer data to be drawn

	float vertexBufferData[] = {
		-0.5, -0.5, 0.0, // 1
		0.5,  -0.5, 0.0, // 2
		0.0,  0.5,	0.0, // 3
	};

	float colorBufferData[] = {
		1, 0, 0, // 1
		0, 1, 0, // 1
		0, 0, 1, // 1
	};

	triangle.genBuffers(2);
	triangle.setVertexAmount(3);
	triangle.setMode(GL_TRIANGLES);
	triangle.setBufferData(0, vertexBufferData, 3);
	triangle.setBufferData(1, colorBufferData, 3);

	// render loop (end if the window should close)

	while (!event.windowClose())
	{
		// poll for window events

		event.pollWindow();

		// clear the window

		window.clear();

		// draw the triangle

		window.drawPrimative(triangle);

		// display the triangle

		window.display();
	}

	// cleanup

	triangle.deleteData();
	shader.deleteProgram();
	window.close();

	return 0;
}
