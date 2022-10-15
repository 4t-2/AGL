#include "../../../AGL/agl.hpp"
#include "../inc/Planet.hpp"

#define HEIGHT 1000
#define WIDTH  1000

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
	shader.loadFromFile("vert.vert", "frag.frag");
	window.getShaderUniforms(shader);
	shader.use();

	agl::Camera camera;
	camera.setOrthographicProjection(0, WIDTH, HEIGHT, 0, 0.1, 100);
	camera.setView({0, 0, 1}, {0, 0, 0}, {0, 1, 0});
	window.updateMvp(camera);

	agl::Texture texture;
	texture.setBlank();

	Planet planet(texture, {0, 0}, 100, 100, agl::Color::Green, false);
	Planet other(texture, {0, 0}, 100, 100, agl::Color::Blue, false);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollPointer();

		agl::Vec2i pos = event.getPointerWindowPosition();
		planet.setPosition({(float)pos.x, (float)pos.y});
			
		other.updateAcceleration(planet);
		other.updateVelocity();
		other.updatePosition();

		window.clear();
		drawPlanet(window, planet);
		drawPlanet(window, other);
		window.display();
	}
}

// TODO
// Add a sun shader (lighting too maybe?)
// text
