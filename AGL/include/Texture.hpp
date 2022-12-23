#pragma once

#include "Vec.hpp"
#include "external.hpp"

namespace agl
{
	class Texture
	{
		private:
			unsigned int textureID = 0;
			Vec<int, 2> size = {0, 0};

		public:
			Texture();

			void genTexture();
			static void bind(Texture texture);
			static void setImage(int format, Vec<int, 2> size, unsigned char *data);
			static void setParameter(int pname, int parameter);

			void loadFromFile(const char *filePath);
			void setBlank();
			void useNearestFiltering();
			void useLinearFiltering();

			void deleteTexture();

			unsigned int getTextureID();
			Vec<int, 2> getSize();
	};
} // namespace agl
