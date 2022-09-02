#include "../AGL/agl.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define SPEED 10

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	glm::mat4		  MPV;
	window.setup2D(500, 500, "winfloat", 60, {127, 127, 127}, &MPV);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("./vert.vert", "./frag.frag");

	agl::Rectangle rect;
	rect.setColor(agl::Color::Green);
	rect.setPosition({100, 100});
	rect.setSize({300, 300});

	GLuint MatrixID = glGetUniformLocation(shader.getProgramID(), "MVP");
	window.useShader(shader);
	shader.setUniformMatrix4fv(MatrixID, &MPV[0][0]);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawShape(rect);

		window.display();
	}

	window.close();

	shader.remove();

	return 0;
}
