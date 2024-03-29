#include "../../../AGL/agl.hpp"
#include "../inc/Planet.hpp"

#define WIDTH  1920
#define HEIGHT 1080

#define PLANETS 3

void drawPlanet(agl::RenderWindow &window, Planet &planet)
{
	window.drawShape(*planet.getShape());

	return;
}

int main()
{
	agl::RenderWindow window;
	window.setup({WIDTH, HEIGHT}, "OrbitSim");
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
		Planet(texture, {(float)WIDTH / 2, (float)HEIGHT / 2}, 10000, 100, agl::Color::Yellow, false),
		Planet(texture, {((float)WIDTH / 3) * 2, (float)HEIGHT / 2}, 1, 5, agl::Color::Gray, false),
		Planet(texture, {((float)WIDTH / 4) * 3, (float)HEIGHT / 2}, 70, 25, agl::Color::Blue, false),
	};

	planet[0].setVelocity({0, 0});
	planet[1].setVelocity({0, 6});
	planet[2].setVelocity({0, 3});

	while (!event.windowClose())
	{
		event.poll();

		for (int i = 0; i < PLANETS; i++)
		{
			for (int x = 0; x < PLANETS; x++)
			{
				if (x == i)
				{
					continue;
				}

				planet[i].updateAcceleration(planet[x]);
			}
		}

		for (int i = 0; i < PLANETS; i++)
		{
			planet[i].updateVelocity();
			planet[i].updatePosition();
		}

		window.clear();

		drawPlanet(window, planet[0]);
		drawPlanet(window, planet[1]);
		drawPlanet(window, planet[2]);

		window.display();

		planet[0].setPosition(event.getPointerWindowPosition());
	}

	texture.deleteTexture();
	shader.deleteProgram();
	window.close();
}

// TODO
// Add a sun shader (lighting too maybe?)
// text
