#include "../../../AGL/agl.hpp"

int main()
{
	agl::RenderWindow window;
	window.setup({1920, 1080}, "text");
	window.setClearColor(agl::Color::Gray);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("vert.glsl", "frag.glsl");
	window.getShaderUniforms(shader);
	shader.use();

	agl::Camera camera;
	camera.setOrthographicProjection(0, 1920, 1080, 0, 0.1, 100);
	camera.setView({0, 0, 10}, {0, 0, 0}, {0, 1, 0});
	window.updateMvp(camera);

	agl::Font font;
	font.setup("/usr/share/fonts/TTF/Arial.TTF", 48);
	font.getTexture()->useLinearFiltering();

	agl::Texture blank;
	blank.setBlank();

	agl::Text text;
	text.setFont(&font);

	std::string str = "Hello";

	agl::Rectangle rectangle;
	rectangle.setColor(agl::Color::White);
	rectangle.setPosition({100, 100, -1});
	rectangle.setSize({100, 100});
	rectangle.setTexture(&blank);

	text.setText(str);
	text.setScale(.5);
	text.setPosition({100, 100, 0});
	text.setColor(agl::Color::Blue);

	while (!event.windowClose())
	{
		event.poll();

		window.clear();

		window.drawShape(rectangle);
		window.drawText(text, 100, agl::Right);

		window.display();
	}

	text.clearText();
	font.deleteFont();
	blank.deleteTexture();
	shader.deleteProgram();
	window.close();
}
