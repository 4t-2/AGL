#pragma once

#include "GL/glew.h"

#include "Vec3f.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GL/gl.h"

namespace agl
{
	class Camera
	{
		private:
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 MVP;
			GLuint	  matrixID;

		public:
			void setPerspectiveProjection(float fov, float aspectRatio, float near, float far);
			void setOrthographicProjection(float left, float right, float bottom, float top, float near, float far);
			void setView(Vec3f pos, Vec3f target, Vec3f head);

			void setMatrixID(GLuint matrixID);

			glm::mat4 getMVP();
			GLuint	  getMatrixID();
	};
} // namespace agl
