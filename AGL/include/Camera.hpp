#pragma once

#include "Mat.hpp"
#include "Shader.hpp"

namespace agl
{
	class Camera
	{
		private:
			agl::Mat4f projection;
			agl::Mat4f view;
			
			int mvpID;

		public:
			void setPerspectiveProjection(float fov, float aspectRatio, float near, float far);
			void setOrthographicProjection(float left, float right, float bottom, float top, float near, float far);
			void setView(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head);

			Mat4f getMVP();
	};
} // namespace agl
