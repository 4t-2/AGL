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

	agl::Text text;
	text.setFont(&font);

	std::string str = "Hello World\nThis is a new line!";

	text.setText(str);
	text.setScale(2);
	text.setPosition({100, 100, 0});

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
