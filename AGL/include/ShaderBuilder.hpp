#pragma once

#include <string>

namespace agl
{
	class ShaderElement
	{
		public:
			std::string test = "1";
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

			template<typename...Element>
			void setMain(Element...element)
			{

			}

			std::string getSrc();
	};
} // namespace agl
