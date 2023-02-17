#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace agl
{
	class ShaderElement
	{
		public:
			std::string	   code;

			ShaderElement(std::string str)
			{
				code = str;
			}
	};

	class ShaderBuilder
	{
		private:
			std::string in;
			std::string out;
			std::string uniform;
			std::string main;

		public:
			void addIn(std::string type, std::string name);
			void addOut(std::string type, std::string name);
			void addUniform(std::string type, std::string name);

			void setMain(std::vector<ShaderElement> element)
			{
				for(ShaderElement element : element)
				{
					main += element.code;
				}
			}

			std::string getSrc();
	};
} // namespace agl
