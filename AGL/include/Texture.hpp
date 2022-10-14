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
			void setBlank();

			static void bind(int textureID);

			void deleteTexture();

			unsigned int getTextureID();
	};
} // namespace agl
