#pragma once

namespace agl
{
	class Vec3f
	{
		public:
			float x = 0;
			float y = 0;
			float z = 0;

		Vec3f operator-(Vec3f vector);
	};
} // namespace agl
