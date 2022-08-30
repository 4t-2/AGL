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

	agl::Rectangle rectangle;
	rectangle.setSize({100, 100});
	rectangle.setPosition({100, 100});
	rectangle.setColor(agl::Color::Red);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		// window.drawPrimative(triangle1);
		window.drawShape(rectangle);

		window.display();

		if (event.isKeyPressed(XK_space))
		{
			rectangle.setColor(agl::Color::Blue);
		}
		else
		{
			rectangle.setColor(agl::Color::Red);
		}
	}

	window.close();

	shader.remove();

	return 0;
}
