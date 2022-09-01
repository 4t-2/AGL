#include "../AGL/agl.hpp"

#define SPEED 10

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	window.setup2D(500, 500, "winfloat", 60, {127, 127, 127});

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadShaders("./vert.vert", "./frag.frag");

	window.useShader(shader);

	agl::Rectangle rectangle;
	rectangle.setSize({500, 500});
	rectangle.setPosition({0, 0});
	rectangle.setColor(agl::Color::Red);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

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
