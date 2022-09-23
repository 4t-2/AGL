#include "../AGL/agl.hpp"
#include "../AGL/include/Mat4f.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#define TITLE  "winfloat"
#define WIDTH  500.
#define HEIGHT 500.
#define FPS	   60
#define CLEARCOLOR         \
	{                      \
		127, 127, 127, 127 \
	}

namespace matFunc
{

	void translate(glm::mat4 &mat, agl::Vec3f position)
	{
		mat[3][3] = 1.0f;

		mat[0][0] = 1.0f;
		mat[1][1] = 1.0f;
		mat[2][2] = 1.0f;

		mat[3][0] = position.x;
		mat[3][1] = position.y;
		mat[3][2] = position.z;

		return;
	}

	void scale(glm::mat4 &mat, agl::Vec3f size)
	{
		mat[3][3] = 1.0f;

		mat[0][0] = size.x;
		mat[1][1] = size.y;
		mat[2][2] = size.z;

		return;
	}

	void rotateX(glm::mat4 &mat, float x)
	{
		mat[3][3] = 1.0f;
		mat[0][0] = 1.0f;

		float xSin = sin(x * 3.14 / 180);
		float xCos = cos(x * 3.14 / 180);

		mat[1][1] = xCos;
		mat[2][2] = xCos;
		mat[1][2] = xSin;
		mat[2][1] = -xSin;

		return;
	}

	void rotateY(glm::mat4 &mat, float y)
	{
		mat[1][1] = 1.0f;
		mat[3][3] = 1.0f;

		float ySin = sin(y * 3.14 / 180);
		float yCos = cos(y * 3.14 / 180);

		mat[0][0] = yCos;
		mat[2][2] = yCos;
		mat[0][2] = ySin;
		mat[2][0] = -ySin;

		return;
	}

	void rotateZ(glm::mat4 &mat, float z)
	{
		mat[2][2] = 1.0f;
		mat[3][3] = 1.0f;

		float zSin = sin(z * 3.14 / 180);
		float zCos = cos(z * 3.14 / 180);

		mat[0][0] = zCos;
		mat[1][1] = zCos;
		mat[1][0] = zSin;
		mat[0][1] = -zSin;

		return;
	}

} // namespace matFunc

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
	rectangle.setSize({1, 1, 1});
	rectangle.setPosition(position);
	rectangle.setColor(agl::Color::Blue);

	agl::Camera camera;
	camera.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	shader.use();
	int mvpID		= shader.getUniformLocation("MVP");
	int transformID = shader.getUniformLocation("Transform");
	shader.setUniformMatrix4fv(mvpID, &camera.getMVP()[0][0]);

	agl::Vec2i offset;

	glm::mat4  glmMat1 = glm::mat4();
	glm::mat4  glmMat2 = glm::mat4();
	glm::mat4  glmMat3 = glm::mat4();
	glm::vec4  glmVec1;
	glmVec1.x = 1;
	glmVec1.y = 2;
	glmVec1.z = 3;
	glmVec1.w = 4;
	glm::vec4  glmVec2;
	
	agl::Mat4f aglMat1;
	agl::Mat4f aglMat2;
	agl::Mat4f aglMat3;
	agl::Vec4f aglVec1;
	aglVec1.x = 1;
	aglVec1.y = 2;
	aglVec1.z = 3;
	aglVec1.w = 4;
	agl::Vec4f aglVec2;

	matFunc::translate(glmMat1, {6.0f, 7.0f, 8.0f});
	matFunc::scale(glmMat2, {1, 2, 3});
	glmMat3 = glmMat1 * glmMat2;
	glmVec2 = glmMat3 * glmVec1;

	aglMat1.translate({6, 7, 8});
	aglMat2.scale({1, 2, 3});
	aglMat3 = aglMat1 * aglMat2;
	aglVec2 = aglMat3 * aglVec1;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			printf("%f ", glmMat3[y][x]);
		}
		printf("\n");
	}
	printf("%f %f %f %f\n", aglVec2.x, aglVec2.y, aglVec2.z, aglVec2.w);

	printf("\n");

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			printf("%f ", aglMat3.data[y][x]);
		}
		printf("\n");
	}
	printf("%f %f %f %f\n", glmVec2.x, glmVec2.y, glmVec2.z, glmVec2.w);

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		window.drawShape(cuboid, shader, transformID);

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

		cuboid.setSize(size);
		cuboid.setPosition(position);
		cuboid.setRotation(rotation);
	}

	shader.deleteProgram();

	window.close();

	return 0;
}
