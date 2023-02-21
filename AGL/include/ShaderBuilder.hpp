#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace agl
{
	class ShaderElement
	{
		public:
			std::string code;
	};

	class Value : public ShaderElement
	{
		public:
			template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
			Value(T &&value)
			{
				code = std::to_string(value);
			}

			Value(std::string &&value)
			{
				code = value;
			}

			Value operator+(Value &&value)
			{
				return code + "+" + value.code;
			}

			Value operator-(Value &&value)
			{
				return code + "-" + value.code;
			}

			Value operator*(Value &&value)
			{
				return code + "*" + value.code;
			}

			Value operator/(Value &&value)
			{
				return code + "/" + value.code;
			}

			Value operator=(Value &&value)
			{
				return code + "=" + value.code;
			}

			Value operator==(Value &&value)
			{
				return code + "==" + value.code;
			}
	};

	class ControlStructure : public ShaderElement
	{
		public:
			ControlStructure(std::string name, Value &&value, std::vector<ShaderElement> element)
			{
				code += name + "(" + value.code + ")\n{\n";

				for(ShaderElement element : element)
				{
					code += element.code + ";\n";
				}

				code += "}";
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
