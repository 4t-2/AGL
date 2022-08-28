#include "../AGL/agl.hpp"

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	window.setup(500, 500, "winfloat", 60);

	agl::Event event;
	event.setWindow(window);

	agl::GLPrimative triangle1;

	float vertexBufferData[9] = {0, -0.5, 0, -1.0, -0.5, 0, -0.5, 0.5, 0};
	float colorBufferData[9]  = {1, 0, 0, 0, 1, 0, 0, 0, 1};

	triangle1.setMode(GL_TRIANGLES);
	triangle1.setVertexData(vertexBufferData, sizeof(vertexBufferData));
	triangle1.setColorData(colorBufferData, sizeof(colorBufferData));

	agl::Shader shader;
	shader.loadShaders("./vert.vert", "./frag.frag");

	float i = 0;

	window.useShader(shader);
	XEvent xev;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawPrimative(triangle1);

		window.display();

		if(event.isKeyPressed(XK_Left))
		{
			i += 0.001;
		}

		if(event.isKeyPressed(XK_Right))
		{
			i -= 0.001;
		}

		for(int x = 0; x < 9; x++)
		{
			colorBufferData[x] += i;
		}
		printf("%lu\n", sizeof(vertexBufferData));
		triangle1.setColorData(colorBufferData, sizeof(vertexBufferData));
	}

	window.close();

	shader.remove();

	return 0;
}
