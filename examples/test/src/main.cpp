#include "../../../AGL/agl.hpp"

int main()
{
	agl::RenderWindow window;
	window.setup({500, 500}, "winfloat");  // setup X and OpenGL parts
	window.setClearColor({127, 127, 127}); // set the clear color
	window.setFPS(30);					   // set the FPS

	agl::Event	   event;
	agl::Camera	   camera;
	agl::Shader	   shader;
	agl::Rectangle rectangle;
	agl::Texture   texture;

	// enable events

	event.setWindow(window);

	// setup and use the shaders

	shader.v2loadFromFile("./vert.glsl", "./frag.glsl", "./geom.glsl");

	window.getShaderUniforms(shader); // get the locations transform, mvp and shapeColor uniforms
	shader.use();					  // use the shader

	// setup camera for 3D rendering

	camera.setOrthographicProjection(0, 1000, 1000, 0, 0.1, 100);

	camera.setView({0, 0, 10}, {0, 0, 0}, {0, 1, 0});

	window.updateMvp(camera);

	// setup blank texture
	texture.setBlank();

	// setup shapes

	rectangle.setColor({255, 0, 0});
	rectangle.setTexture(&texture);
	rectangle.setPosition(agl::Vec<float, 3>{500, 500, 0});
	rectangle.setSize(agl::Vec<float, 3>{400, 400, 0});
	rectangle.setRotation(agl::Vec<float, 3>{0, 0, 45});
	rectangle.setOffset({0, 0, 0});

	agl::Vec<float, 3> offset	= {0, 0, 0};
	int				   rotation = 1;

	// render loop (end if the window should close)

	while (!event.windowClose())
	{
		// poll for window events

		event.poll();

		// clear the window

		window.clear();

		// draw the triangle

		window.drawShape(rectangle);

		// display the triangle

		window.display();

		if (event.isKeyPressed(agl::Key::Up))
		{
			offset.y += 5;
		}
		if (event.isKeyPressed(agl::Key::Down))
		{
			offset.y -= 5;
		}
		if (event.isKeyPressed(agl::Key::Left))
		{
			offset.x -= 5;
		}
		if (event.isKeyPressed(agl::Key::Right))
		{
			offset.x += 5;
		}

		if (event.isPointerButtonPressed(agl::Button::Middle))
		{
			offset.x += 5;
		}

		if (event.scroll == agl::Up)
		{
			offset.y += 5;
			// std::cout << "up" << '\n';
		}
		if (event.scroll == agl::Down)
		{
			offset.y -= 5;
		}

		rotation++;

		rectangle.setOffset(offset);
		rectangle.setRotation(agl::Vec<float, 3>{0, 0, (float)rotation});

		// std::cout << window.getState().size << '\n';
		// std::cout << window.getState().pos << '\n';

		static int theme = 0;

		if (rotation % 120 == 0)
		{
			theme++;

			if (theme > 5)
			{
				theme = 0;
			}

			// std::cout << theme << '\n';

			switch (theme)
			{
				case 0:
					window.setCursorShape(agl::CursorType::Arrow);
					break;
				case 1:
					window.setCursorShape(agl::CursorType::Beam);
					break;
				case 2:
					window.setCursorShape(agl::CursorType::Crosshair);
					break;
				case 3:
					window.setCursorShape(agl::CursorType::Hand);
					break;
				case 4:
					window.setCursorShape(agl::CursorType::HorResize);
					break;
				case 5:
					window.setCursorShape(agl::CursorType::VerResize);
					break;
			}
		}

		for (const int i : event.keybuffer)
		{
			std::cout << i << '\n';
		}
	}

	// cleanup

	texture.deleteTexture();
	shader.deleteProgram();
	window.close();

	return 0;
}
