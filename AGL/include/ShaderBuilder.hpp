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
			Value(const Value &value)
			{
				code = value.code;
			}

			template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
			Value(const T &value)
			{
				code = std::to_string(value);
			}

			Value(const std::string &value)
			{
				code = value;
			}

			Value operator+(const Value &value)
			{
				return Value(code + "+" + value.code);
			}

			Value operator-(const Value &value)
			{
				return Value(code + "-" + value.code);
			}

			Value operator*(const Value &value)
			{
				return Value(code + "*" + value.code);
			}

			Value operator/(const Value &value)
			{
				return Value(code + "/" + value.code);
			}

			Value operator=(const Value &value)
			{
				return Value(code + "=" + value.code);
			}

			Value operator==(const Value &value)
			{
				return Value(code + "==" + value.code);
			}

			static const Value gl_Position;
	};

	typedef Value val;

	class ControlStructure : public ShaderElement
	{
		public:
			ControlStructure(std::string name, ShaderElement controlStatement, std::vector<ShaderElement> element)
			{
				code += name + "(" + controlStatement.code + ")\n{\n";

				for (ShaderElement element : element)
				{
					code += element.code + ";\n";
				}

				code += "}";
			}
	};

	class ShaderIf : public ControlStructure
	{
		public:
			ShaderIf(Value expression, std::vector<ShaderElement> element) : ControlStructure("if", expression, element)
			{
			}
	};

	typedef ShaderIf _if;

	class ShaderWhile : public ControlStructure
	{
		public:
			ShaderWhile(Value expression, std::vector<ShaderElement> element)
				: ControlStructure("while", expression, element)
			{
			}
	};

	typedef ShaderWhile _while;

	class LoopControlStatement : public ShaderElement
	{
		public:
			LoopControlStatement(Value e1, Value e2, Value e3)
			{
				code += e1.code + ";" + e2.code + ";" + e3.code;
			}
	};

	class ShaderFor : public ControlStructure
	{
		public:
			ShaderFor(ShaderElement controlStatement, std::vector<ShaderElement> element)
				: ControlStructure("for", controlStatement, element)
			{
			}
	};

	typedef ShaderFor _for;

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
			Value addLayout(int location, std::string type, std::string name);
			Value addIn(std::string type, std::string name);
			Value addOut(std::string type, std::string name);
			Value addUniform(std::string type, std::string name);

			void setMain(std::vector<ShaderElement> element);

			void setDefaultVert();
			void setDefaultFrag();

			std::string getSrc();
	};
} // namespace agl
