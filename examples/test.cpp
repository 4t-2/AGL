#include "../AGL/agl.hpp"

#define SPEED 10

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	window.setup2D(500, 500, "winfloat", 60, {127, 127, 127});

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
	rectangle.setSize({499, 499});
	rectangle.setPosition({0, 0});
	rectangle.setColor(agl::Color::Red);

	agl::Rectangle box;
	box.setSize({200, 200});
	box.setPosition({200, 200});
	box.setColor(agl::Color::Blue);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		// window.drawPrimative(triangle1);
		window.drawShape(box);
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

		agl::Vec2f pos = rectangle.getPosition();

		if(event.isKeyPressed(XK_Up))
		{
			pos.y+=SPEED;
		} if(event.isKeyPressed(XK_Down))
		{
			pos.y-=SPEED;
		} if(event.isKeyPressed(XK_Left))
		{
			pos.x-=SPEED;
		} if(event.isKeyPressed(XK_Right))
		{
			pos.x+=SPEED;
		}

		if(event.isKeyPressed(XK_space))
		{
			printf("cringe\n");
		}

		rectangle.setPosition(pos);
	}

	window.close();

	shader.remove();

	return 0;
}
