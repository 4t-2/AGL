#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace agl
{
	class ShaderElement
	{
		public:
			std::string code;
	};

	class Assign : public ShaderElement
	{
		public:
			Assign(std::string lvalue, std::string rvalue)
			{
				code = lvalue + " = " + rvalue;
			}
	};

	static const std::string vec2 = "vec2";
	static const std::string vec3 = "vec3";
	static const std::string vec4 = "vec4";
	
	static const std::string mat4 = "mat4";

	static const std::string sampler2D = "sampler2D";

	class ShaderBuilder
	{
		private:
			std::string layout;
			std::string in;
			std::string out;
			std::string uniform;
			std::string main;

		public:
			void addLayout(int location, std::string type, std::string name);
			void addIn(std::string type, std::string name);
			void addOut(std::string type, std::string name);
			void addUniform(std::string type, std::string name);

			void setMain(std::vector<ShaderElement> element);

			std::string getSrc();
	};
} // namespace agl
