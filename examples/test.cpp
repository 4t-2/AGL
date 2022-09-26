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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	// glGenerateMipmap(GL_TEXTURE_2D);

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

	agl::Camera camera;
	camera.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, -1.0f, // 1
		-1.0f, -1.0f, 1.0f,	 // 2
		-1.0f, 1.0f,  1.0f,	 // 3
		1.0f,  1.0f,  -1.0f, // 4
		-1.0f, -1.0f, -1.0f, // 5
		-1.0f, 1.0f,  -1.0f, // 6
		1.0f,  -1.0f, 1.0f,	 // 7
		-1.0f, -1.0f, -1.0f, // 8
		1.0f,  -1.0f, -1.0f, // 9
		1.0f,  1.0f,  -1.0f, // 10
		1.0f,  -1.0f, -1.0f, // 11
		-1.0f, -1.0f, -1.0f, // 12
		-1.0f, -1.0f, -1.0f, // 13
		-1.0f, 1.0f,  1.0f,	 // 14
		-1.0f, 1.0f,  -1.0f, // 15
		1.0f,  -1.0f, 1.0f,	 // 16
		-1.0f, -1.0f, 1.0f,	 // 17
		-1.0f, -1.0f, -1.0f, // 18
		-1.0f, 1.0f,  1.0f,	 // 19
		-1.0f, -1.0f, 1.0f,	 // 20
		1.0f,  -1.0f, 1.0f,	 // 21
		1.0f,  1.0f,  1.0f,	 // 22
		1.0f,  -1.0f, -1.0f, // 23
		1.0f,  1.0f,  -1.0f, // 24
		1.0f,  -1.0f, -1.0f, // 25
		1.0f,  1.0f,  1.0f,	 // 26
		1.0f,  -1.0f, 1.0f,	 // 27
		1.0f,  1.0f,  1.0f,	 // 28
		1.0f,  1.0f,  -1.0f, // 29
		-1.0f, 1.0f,  -1.0f, // 30
		1.0f,  1.0f,  1.0f,	 // 31
		-1.0f, 1.0f,  -1.0f, // 32
		-1.0f, 1.0f,  1.0f,	 // 33
		1.0f,  1.0f,  1.0f,	 // 34
		-1.0f, 1.0f,  1.0f,	 // 35
		1.0f,  -1.0f, 1.0f	 // 36
	};

	GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f, // 1
		0.000103f, 1.0f - 0.336048f, // 2
		0.335973f, 1.0f - 0.335903f, // 3
		1.000023f, 1.0f - 0.000013f, // 4
		0.667979f, 1.0f - 0.335851f, // 5
		0.999958f, 1.0f - 0.336064f, // 6
		0.667979f, 1.0f - 0.335851f, // 7
		0.336024f, 1.0f - 0.671877f, // 8
		0.667969f, 1.0f - 0.671889f, // 9
		1.000023f, 1.0f - 0.000013f, // 10
		0.668104f, 1.0f - 0.000013f, // 11
		0.667979f, 1.0f - 0.335851f, // 12
		0.000059f, 1.0f - 0.000004f, // 13
		0.335973f, 1.0f - 0.335903f, // 14
		0.336098f, 1.0f - 0.000071f, // 15
		0.667979f, 1.0f - 0.335851f, // 16
		0.335973f, 1.0f - 0.335903f, // 17
		0.336024f, 1.0f - 0.671877f, // 18
		1.000004f, 1.0f - 0.671847f, // 19
		0.999958f, 1.0f - 0.336064f, // 20
		0.667979f, 1.0f - 0.335851f, // 21
		0.668104f, 1.0f - 0.000013f, // 22
		0.335973f, 1.0f - 0.335903f, // 23
		0.667979f, 1.0f - 0.335851f, // 24
		0.335973f, 1.0f - 0.335903f, // 25
		0.668104f, 1.0f - 0.000013f, // 26
		0.336098f, 1.0f - 0.000071f, // 27
		0.000103f, 1.0f - 0.336048f, // 28
		0.000004f, 1.0f - 0.671870f, // 29
		0.336024f, 1.0f - 0.671877f, // 30
		0.000103f, 1.0f - 0.336048f, // 31
		0.336024f, 1.0f - 0.671877f, // 32
		0.335973f, 1.0f - 0.335903f, // 33
		0.667969f, 1.0f - 0.671889f, // 34
		1.000004f, 1.0f - 0.671847f, // 35
		0.667979f, 1.0f - 0.335851f	 // 36
	};

	agl::GLPrimative cube;
	cube.genBuffers(2);
	cube.setVertexAmount(36);
	cube.setMode(GL_TRIANGLES);
	cube.setBufferData(0, g_vertex_buffer_data, 3);
	cube.setBufferData(1, g_uv_buffer_data, 2);

	agl::Texture UVTexture;
	UVTexture.loadFromFile("./uvtemplate.bmp");

	shader.use();
	int	   mvpID	 = shader.getUniformLocation("MVP");
	UVTexture.setTextureSampler(shader.getUniformLocation("myTextureSampler"));
	shader.setUniformMatrix4fv(mvpID, &camera.getMVP()[0][0]);

	agl::Vec3f pos = {4, 3, 3};

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		UVTexture.bind();

		window.clear();

		window.drawPrimative(cube);

		window.display();

		static float speed = 0.01;

		if (event.isKeyPressed(XK_Left))
		{
			pos.x -= speed;
		}
		if (event.isKeyPressed(XK_Right))
		{
			pos.x += speed;
		}
		if (event.isKeyPressed(XK_space))
		{
			pos.y += speed;
		}
		if (event.isKeyPressed(XK_Control_L))
		{
			pos.y -= speed;
		}
		if (event.isKeyPressed(XK_Up))
		{
			pos.z -= speed;
		}
		if (event.isKeyPressed(XK_Down))
		{
			pos.z += speed;
		}

		camera.setView(pos, {0, 0, 0}, {0, 1, 0});
		shader.setUniformMatrix4fv(mvpID, &camera.getMVP()[0][0]);
	}

	cube.deleteData();

	shader.deleteProgram();

	UVTexture.deleteTexture();

	window.close();

	return 0;
}
