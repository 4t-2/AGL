#include <GL/glew.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include "../AGL/agl.hpp"

int main(int argc, char *argv[])
{

	agl::RenderWindow window;
	window.setup(500, 500, "winfloat", 60);

	agl::GLPrimative triangle1;

	agl::Vector3f vertex1[6];
	vertex1[0] = {0, -0.5, 0};
	vertex1[1] = {-1.0, -0.5, 0};
	vertex1[2] = {-.5, 0.5, 0};

	vertex1[3] = {1, -0.5, 0};
	vertex1[4] = {0.0, -0.5, 0};
	vertex1[5] = {.5, 0.5, 0};

	triangle1.setMode(GL_TRIANGLES);
	triangle1.setVertices(vertex1, sizeof(vertex1));

	agl::GLPrimative triangle2;

	agl::Vector3f vertex2[3];
	vertex2[0] = {1, -0.5, 0};
	vertex2[1] = {0.0, -0.5, 0};
	vertex2[2] = {.5, 0.5, 0};

	triangle2.setMode(GL_TRIANGLES);
	triangle2.setVertices(vertex2, sizeof(vertex2));

	agl::Shader shader;
	shader.loadShaders("./vert.vert", "./frag.frag");

	float i = 0;

	window.useShader(shader);
	XEvent event;

	while (!window.shouldClose(event))
	{
		event = window.getEvent(event);

		char c[32];
		XQueryKeymap(window.getDisplay(), c);

		for (int i = 0; i < 32; i++)
		{
			if(c[i])
			{
				printf("byte %d\n", i);
			}
			printf("%d", (c[i] & 0b10000000) ? 1 : 0);
			printf("%d", (c[i] & 0b01000000) ? 1 : 0);
			printf("%d", (c[i] & 0b00100000) ? 1 : 0);
			printf("%d", (c[i] & 0b00010000) ? 1 : 0);
			printf("%d", (c[i] & 0b00001000) ? 1 : 0);
			printf("%d", (c[i] & 0b00000100) ? 1 : 0);
			printf("%d", (c[i] & 0b00000010) ? 1 : 0);
			printf("%d", (c[i] & 0b00000001) ? 1 : 0);
		}

		printf("\n\n");

		if(c[3]&0b00000001)
		{
			printf("q");
		}

		window.clear();

		window.drawPrimative(triangle1);
		window.display();

		if (0)
		{
			i += 0.001;
			printf("%d\n", event.xkey.keycode);
			vertex1[2].x += i;

			triangle1.setVertices(vertex1, sizeof(vertex1));
		}
	}

	window.close();

	shader.remove();

	return 0;
}
