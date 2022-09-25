#include "../AGL/agl.hpp"
#include "../AGL/include/Mat4f.hpp"

#define TITLE  "winfloat"
#define WIDTH  500.
#define HEIGHT 500.
#define FPS	   60
#define CLEARCOLOR         \
	{                      \
		127, 127, 127, 127 \
	}

GLuint loadBMP_custom(const char *imagepath)
{

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int  dataPos;
	unsigned int  imageSize;
	unsigned int  width, height;
	// Actual RGB data
	unsigned char *data;

	// Open the file
	FILE *file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("%s could not be opened. Are you in the right directory ? Don't "
			   "forget to read the FAQ !\n",
			   imagepath);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int *)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	if (*(int *)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}

	// Read the information about the image
	dataPos	  = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	width	  = *(int *)&(header[0x12]);
	height	  = *(int *)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify
	// this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	// Poor filtering, or ...
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	GLint			  attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	window.openDisplay();
	window.createRootWindow();
	window.createColormap(attribute, AllocNone);
	window.setEventMask(ExposureMask | KeyPressMask);
	window.createWindow(0, 0, WIDTH, HEIGHT, CWColormap | CWEventMask);
	window.setTitle(TITLE);

	XWindowAttributes gwa = window.getWindowAttributes();

	window.initGL();
	window.setViewport(0, 0, gwa.width, gwa.height);
	window.setClearColor(CLEARCOLOR);
	window.setFPS(FPS);
	window.mapWindow();

	window.GLEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("./vert.vert", "./frag.frag");

	agl::Vec3f size		= {1, 1, 1};
	agl::Vec3f position = {0, 0, 0};
	agl::Vec3f rotation = {0, 0, 0};

	agl::Cuboid cuboid;
	cuboid.setSize({1, 1, 1});
	cuboid.setPosition(position);
	cuboid.setColor(agl::Color::Blue);

	agl::Circle circle(100);
	circle.setSize(size);
	circle.setPosition(position);
	circle.setColor(agl::Color::Red);

	agl::Rectangle rectangle;

	agl::Camera camera;
	camera.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	GLuint image = loadBMP_custom("./uvtemplate.bmp");

	shader.use();
	int mvpID		= shader.getUniformLocation("MVP");
	int transformID = shader.getUniformLocation("Transform");
	shader.setUniformMatrix4fv(mvpID, &camera.getMVP()[0][0]);

	agl::Vec2i offset;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawShape(rectangle, shader, transformID);

		window.display();

		float speed = 0.04;

		if (event.isKeyPressed(XK_Left))
		{
			position.x -= speed;
		}
		if (event.isKeyPressed(XK_Right))
		{
			position.x += speed;
		}
		if (event.isKeyPressed(XK_Up))
		{
			position.y += speed;
		}
		if (event.isKeyPressed(XK_Down))
		{
			position.y -= speed;
		}

		if (event.isKeyPressed(XK_a))
		{
			size.x -= speed;
		}
		if (event.isKeyPressed(XK_d))
		{
			size.x += speed;
		}
		if (event.isKeyPressed(XK_w))
		{
			size.y += speed;
		}
		if (event.isKeyPressed(XK_s))
		{
			size.y -= speed;
		}

		if (event.isKeyPressed(XK_f))
		{
			rotation.x -= speed * 10;
		}
		if (event.isKeyPressed(XK_h))
		{
			rotation.x += speed * 10;
		}
		if (event.isKeyPressed(XK_t))
		{
			rotation.y += speed * 10;
		}
		if (event.isKeyPressed(XK_g))
		{
			rotation.y -= speed * 10;
		}

		circle.setSize(size);
		circle.setPosition(position);
		circle.setRotation(rotation);
	}

	shader.deleteProgram();

	window.close();

	return 0;
}
