#pragma once

#include "external.hpp"

namespace agl
{
	class Texture
	{
		private:
			unsigned int textureID;
			unsigned int textureSampler;

		public:
			int loadFromFile(const char *filePath);

			void setTextureSampler(unsigned int textureSampler);

			void bind();

			void deleteTexture();

			unsigned int getTextureID();
			unsigned int getTextureSampler();
	};
} // namespace agl
