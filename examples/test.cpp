#include <GL/glew.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include "../AGL/agl.hpp"

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	window.setup(500, 500, "winfloat", 60);

	agl::Event event;
	event.setWindow(window);

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
	XEvent xev;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawPrimative(triangle1);
		
		window.display();

		if(event.isPointerButtonPressed(Button1Mask))
		{
			agl::Vector2i pos = event.getPointerWindowPosition();
			printf("%d\n%d\n\n", pos.x, pos.y);
		}
	}

	window.close();

	shader.remove();

	return 0;
}
