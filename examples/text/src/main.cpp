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
	font.setup();

	agl::Text text;
	text.setFont(&font);

	text.setText("hello", 5);

	agl::Rectangle test;
	test.setSize({900, 900, 0});
	test.setPosition({100, 100, 0});
	test.setTexture(font.getTexture());
	test.setColor(agl::Color::White);

	agl::Vec<float, 3> scale = font.getGlyph('e')->scale;
	std::cout << scale << '\n';
	agl::Vec<float, 3> size = font.getGlyph('e')->size;
	std::cout << size << '\n';
	agl::Vec<float, 3> pos = font.getGlyph('e')->position;
	std::cout << pos << '\n';

	test.setSize(size);

	test.setTextureScaling(scale);
	test.setTextureTranslation(pos);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawText(text);

		window.display();
	}
}
