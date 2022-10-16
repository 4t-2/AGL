#include "../../../AGL/agl.hpp"
#include "../inc/Planet.hpp"

#define HEIGHT 1000
#define WIDTH  1000

#define PLANETS 2

void drawPlanet(agl::RenderWindow &window, Planet &planet)
{
	window.drawShape(*planet.getShape());

	return;
}

int main()
{
	agl::RenderWindow window;
	window.setup({HEIGHT, WIDTH}, "winfloat");
	window.setClearColor({0, 0, 0});
	window.setFPS(60);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("vert.glsl", "frag.glsl");
	window.getShaderUniforms(shader);
	shader.use();

	agl::Camera camera;
	camera.setOrthographicProjection(0, WIDTH, HEIGHT, 0, 0.1, 100);
	camera.setView({0, 0, 1}, {0, 0, 0}, {0, 1, 0});
	window.updateMvp(camera);

	agl::Texture texture;
	texture.setBlank();

	Planet planet[PLANETS] = {
		Planet(texture, {(float)WIDTH / 4, (float)HEIGHT / 2}, 100, 25, agl::Color::Red, false),
		Planet(texture, {(float)WIDTH / 2, (float)HEIGHT / 2}, 100, 25, agl::Color::Green, false),
	};

	planet[0].setVelocity({0, 5});
	planet[1].setVelocity({0, 0});

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollPointer();

		planet[0].updateAcceleration(planet[1]);

		planet[1].updateAcceleration(planet[0]);

		planet[0].updateVelocity();
		planet[0].updatePosition();
		planet[1].updateVelocity();
		planet[1].updateVelocity();

		window.clear();

		for (int i = 0; i < PLANETS; i++)
		{
			drawPlanet(window, planet[i]);
		}

		window.display();
	}
}

// TODO
// Add a sun shader (lighting too maybe?)
// text
