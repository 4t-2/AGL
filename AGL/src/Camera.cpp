#include "../include/Camera.hpp"

void agl::Camera::setPerspectiveProjection(float fov, float aspectRatio, float near, float far)
{
	projection.perspective(fov * 3.1415 / 180, aspectRatio, near, far);

	return;
}

void agl::Camera::setOrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	projection.ortho(left, right, bottom, top, near, far);

	return;
}

void agl::Camera::setView(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head)
{
	view.lookAt({pos.x, pos.y, pos.z}, {target.x, target.y, target.z}, {head.x, head.y, head.z});
}

agl::Mat4f agl::Camera::getMVP()
{
	return projection * view;
}
