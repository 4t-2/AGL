#include "../../../AGL/agl.hpp"

int main()
{
	agl::Vec3f pos = {5, 5, 5};

	// setup window

	agl::RenderWindow window;
	window.setup({500, 500}, "winfloat");  // setup X and OpenGL parts
	window.setClearColor({127, 127, 127}); // set the clear color
	window.setFPS(30);					   // set the FPS

	agl::Event	   event;
	agl::Camera	   camera;
	agl::Shader	   shader;
	agl::Rectangle rectangle;
	agl::Circle	   circle(12); // set circle to have 10 sides
	agl::Cuboid	   cuboid;
	agl::Texture   texture;

	// enable events

	event.setWindow(window);

	// setup and use the shaders

	shader.loadFromFile("./vert.vert",
						"./frag.frag");							   // load frag and vert from file
	window.setTransformID(shader.getUniformLocation("Transform")); // store location of Transform uniform in window
	window.setMvpID(shader.getUniformLocation("MVP"));			   // store location of MVP uniform in window
	window.setUniformColorID(
		shader.getUniformLocation("uniformColor")); // store location of the color uniform in window
	shader.use();									// use the shader

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

	camera.setMvpID(shader.getUniformLocation("MVP"));
	camera.update();

	// setup blank texture
	texture.loadFromFile("blank.bmp");

	// setup shapes

	rectangle.setColor({255, 0, 0});
	rectangle.setTexture(&texture);
	rectangle.setPosition({0, 0, 0});

	circle.setColor({0, 255, 0});
	circle.setTexture(&texture);
	circle.setPosition({2.5, .5, 0});
	circle.setSize({.5, .5, .5});

	cuboid.setColor({0, 0, 255});
	cuboid.setTexture(&texture);
	cuboid.setPosition({-2, 0, 0});

	float speed = 0.1;

	// render loop (end if the window should close)

	while (!event.windowClose())
	{
		camera.setView(pos, {0, 0, 0}, {0, 1, 0});
		camera.update();

		// poll for window events

		event.pollWindow();
		event.pollKeyboard();

		// clear the window

		window.clear();

		// draw the triangle

		window.drawShape(rectangle);
		window.drawShape(circle);
		window.drawShape(cuboid);

		// display the triangle

		window.display();

		if (event.isKeyPressed(XK_Left))
		{
			pos.x -= speed;
		}
		if (event.isKeyPressed(XK_Right))
		{
			pos.x += speed;
		}
		if (event.isKeyPressed(XK_Control_L))
		{
			pos.y -= speed;
		}
		if (event.isKeyPressed(XK_space))
		{
			pos.y += speed;
		}
		if (event.isKeyPressed(XK_Up))
		{
			pos.z -= speed;
		}
		if (event.isKeyPressed(XK_Down))
		{
			pos.z += speed;
		}
	}

	// cleanup

	shader.deleteProgram();
	window.close();

	return 0;
}
