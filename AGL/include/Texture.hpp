#pragma once

#include "external.hpp"

namespace agl
{
	class Texture
	{
		private:
			unsigned int textureID;

		public:
			int loadFromFile(const char *filePath);

			void bind();

			void deleteTexture();

			unsigned int getTextureID();
	};
} // namespace agl
