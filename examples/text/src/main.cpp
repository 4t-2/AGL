#include "../../../AGL/agl.hpp"

int main()
{
	agl::RenderWindow window;
	window.setup({1920, 1080}, "text");

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

	agl::Texture blank;
	blank.setBlank();

	agl::Rectangle test;
	test.setSize(agl::Vec<float, 2>{100, 100});
	test.setPosition(agl::Vec<float, 2>{100, 100});
	test.setTexture(&blank);

	while (!event.windowClose())
	{
		event.pollWindow();

		window.clear();

		window.drawShape(test);

		window.display();
	}

	window.close();
}
