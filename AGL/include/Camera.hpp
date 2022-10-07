#pragma once

#include "Vec3f.hpp"
#include "Shader.hpp"
#include "Mat4f.hpp"

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
			void setView(Vec3f pos, Vec3f target, Vec3f head);

			void setMvpID(int mvpID);
			void update();

			Mat4f getMVP();
	};
} // namespace agl
