#include "../../../AGL/agl.hpp"

int main()
{
	agl::Vec<float, 3> pos = {5, 5, 5};

	// setup window

	agl::RenderWindow window;
	window.setup({500, 500}, "Shapes");	   // setup X and OpenGL parts
	window.setClearColor({127, 127, 127}); // set the clear color
	window.setFPS(30);					   // set the FPS
	window.setSwapInterval(0);			   // Disable vsync

	agl::Event	   event;
	agl::Camera	   camera;
	agl::Shader	   shader;
	agl::Rectangle rectangle;
	agl::Circle	   circle(12); // set circle to have 12 sides
	agl::Cuboid	   cuboid;
	agl::Texture   texture;

	// enable events

	event.setWindow(window);

	// setup and use the shaders

	shader.loadFromFile("./vert.glsl",
						"./frag.glsl"); // load frag and vert from file
	window.getShaderUniforms(shader);	// get the locations transform, mvp and shapeColor uniforms
	shader.use();						// use the shader

	// setup camera for 3D rendering

	camera.setPerspectiveProjection(45,			 // set FOV to 45
									500. / 500., // aspect ration is 1
									0.1,		 // if closer than 0.1 than do not render
									1000		 // if further than 1000 than do not render
	);

	camera.setView(pos,		  // set camera position to 10, 10, 10
				   {0, 0, 0}, // set camera to look at world center (0, 0, 0)
				   {0, 1, 0}  // set camera to be oriented to have the head point up
	);

	// setup texture
	texture.loadFromFile("uvtemplate.bmp");

	// setup shapes

	rectangle.setColor({255, 0, 0});
	rectangle.setTexture(&texture);
	rectangle.setPosition(agl::Vec<float, 3>{0, 0, 0});

	circle.setColor({0, 255, 0});
	circle.setTexture(&texture);
	circle.setPosition(agl::Vec<float, 3>{2.5, .5, 0});
	circle.setSize(agl::Vec<float, 3>{.5, .5, .5});

	cuboid.setColor({0, 0, 255});
	cuboid.setTexture(&texture);
	cuboid.setPosition(agl::Vec<float, 3>{-2, 0, 0});

	float speed = 0.1;

	// render loop (end if the window should close)

	while (!event.windowClose())
	{
		camera.setView(pos, {0, 0, 0}, {0, 1, 0});
		window.updateMvp(camera);

		// poll for window events

		event.poll();

		// clear the window

		window.clear();

		// draw the triangle

		window.drawShape(rectangle);
		window.drawShape(circle);
		window.drawShape(cuboid);

		// display the triangle

		window.display();

		if (event.isKeyPressed(agl::Key::Left))
		{
			pos.x -= speed;
		}
		if (event.isKeyPressed(agl::Key::Right))
		{
			pos.x += speed;
		}
		if (event.isKeyPressed(agl::Key::LeftControl))
		{
			pos.y -= speed;
		}
		if (event.isKeyPressed(agl::Key::Space))
		{
			pos.y += speed;
		}
		if (event.isKeyPressed(agl::Key::Up))
		{
			pos.z -= speed;
		}
		if (event.isKeyPressed(agl::Key::Down))
		{
			pos.z += speed;
		}

		if (event.isKeyPressed(agl::Key::Return))
		{
			texture.useLinearFiltering();
		}
		else
		{
			texture.useNearestFiltering();
		}
	}

	// cleanup

	texture.deleteTexture();
	shader.deleteProgram();
	window.close();

	return 0;
}
