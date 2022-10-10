#include "../../../AGL/agl.hpp"

int main()
{
	agl::RenderWindow window;
	agl::Event		  event;
	agl::Shader		  shader;
	agl::GLPrimative  triangle;

	// setup window

	window.setup({500, 500}, "Triangle"); // setup X and OpenGL parts
	window.setClearColor({0, 0, 0});	  // set the clear color
	window.setFPS(30);					  // set the FPS

	// enable events

	event.setWindow(window);

	// load and use the shaders

	shader.loadFromFile("./vert.vert", "./frag.frag");
	shader.use();

	// set the vertex and buffer data

	// 3 verticies making a triangle
	float vertexBufferData[] = {
		-0.5, -0.5, 0.0, // 1
		0.5,  -0.5, 0.0, // 2
		0.0,  0.5,	0.0, // 3
	};

	// each vertex of the triangle will either be red, green or blue
	// there will be a color gradiant between each of the vertecies
	float colorBufferData[] = {
		1, 0, 0, // 1
		0, 1, 0, // 1
		0, 0, 1, // 1
	};

	triangle.genBuffers(2);			// two buffers so to buffers need to be generated
	triangle.setVertexAmount(3);	// triangle has 3 vertecies
	triangle.setMode(GL_TRIANGLES); // set OpenGL to draw in triangle mode

	triangle.setBufferData(0,				 // set location 0 (vertex data)
						   vertexBufferData, // set location 0 data to vertex data
						   3);				 // each vector has 3 values

	triangle.setBufferData(1,				// set location 0 (vertex data)
						   colorBufferData, // set location 0 data to vertex data
						   3);				// each vector has 3 values

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
