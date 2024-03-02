#include "../include/ShaderBuilder.hpp"

const agl::Value agl::Value::gl_Position = agl::Value("gl_Position");

agl::Value agl::ShaderBuilder::addLayout(int location, std::string type, std::string name)
{
	this->layout += "layout(location=" + std::to_string(location) + ") in " + type + " " + name + ";\n";

	return agl::Value(name);
}

agl::Value agl::ShaderBuilder::addIn(std::string type, std::string name)
{
	in += "in " + type + " " + name + ";\n";

	return agl::Value(name);
}

agl::Value agl::ShaderBuilder::addOut(std::string type, std::string name)
{
	out += "out " + type + " " + name + ";\n";

	return agl::Value(name);
}

agl::Value agl::ShaderBuilder::addUniform(std::string type, std::string name)
{
	uniform += "uniform " + type + " " + name + ";\n";

	return agl::Value(name);
}

void agl::ShaderBuilder::setMain(std::vector<ShaderElement> element)
{
	main = "void main()\n{\n";
	for (ShaderElement element : element)
	{
		main += element.code + ";\n";
	}
	main += "}";
}

void agl::ShaderBuilder::setDefaultVert()
{
	ADD_LAYOUT(0, agl::vec3, position, this);
	ADD_LAYOUT(1, agl::vec2, vertexUV, this);

	ADD_UNIFORM(agl::mat4, transform, this);
	ADD_UNIFORM(agl::mat4, mvp, this);
	ADD_UNIFORM(agl::vec3, shapeColor, this);
	ADD_UNIFORM(agl::mat4, textureTransform, this);

	ADD_OUT(agl::vec2, UVcoord, this);
	ADD_OUT(agl::vec4, fragColor, this);
  
      (void) layoutTotal;
      (void) inTotal;
      (void) outTotal;
      (void) uniformTotal;

	this->setMain({
		UVcoord	  = shaderFunc("vec2", "(" + (textureTransform * shaderFunc("vec4", vertexUV, 1, 1)).code + ").xy"), //
		fragColor = shaderFunc("vec4", shapeColor, 1),																 //
		val(val::gl_Position) = mvp * transform * shaderFunc("vec4", position, 1)									 //
	});
}

void agl::ShaderBuilder::setDefaultFrag()
{
	ADD_IN(agl::vec2, UVcoord, this);
	ADD_IN(agl::vec4, fragColor, this);

	ADD_OUT(agl::vec4, color, this);

	ADD_UNIFORM(agl::sampler2D, myTextureSampler, this);

	this->setMain({
		color = fragColor * shaderFunc("texture", myTextureSampler, UVcoord), //
	});
}

std::string agl::ShaderBuilder::getSrc()
{
	return "#version 330 core\n" + layout + in + out + uniform + main;
}
