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
	val position = this->addLayout(0, agl::vec3, "position");
	val vertexUV = this->addLayout(1, agl::vec2, "vertexUV");

	val transform		 = this->addUniform(agl::mat4, "transform");
	val mvp				 = this->addUniform(agl::mat4, "mvp");
	val shapeColor		 = this->addUniform(agl::vec3, "shapeColor");
	val textureTransform = this->addUniform(agl::mat4, "textureTransform");

	val UVcoord	  = this->addOut(agl::vec2, "UVcoord");
	val fragColor = this->addOut(agl::vec4, "fragColor");

	this->setMain({
		UVcoord				  = val("vec2((textureTransform") * val("vec4(vertexUV, 1, 1)).xy)"), //
		fragColor			  = val("vec4(shapeColor, 1)"),										  //
		val(val::gl_Position) = mvp * transform * val("vec4(position, 1)"),						  //
	});
}

void agl::ShaderBuilder::setDefaultFrag()
{
	val UVcoord	  = this->addIn(agl::vec2, "UVcoord");
	val fragColor = this->addIn(agl::vec4, "fragColor");

	val color = this->addOut(agl::vec4, "color");

	val myTextureSampler = this->addUniform(agl::sampler2D, "myTextureSampler");

	this->setMain({
		color = fragColor * agl::val("texture(myTextureSampler, UVcoord)"), //
	});
}

std::string agl::ShaderBuilder::getSrc()
{
	return "#version 330 core\n" + layout + in + out + uniform + main;
}
