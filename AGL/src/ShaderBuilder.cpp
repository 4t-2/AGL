#include "../include/ShaderBuilder.hpp"

void agl::ShaderBuilder::addLayout(int location, std::string type, std::string name)
{
	this->layout += "layout(location=" + std::to_string(location) + ") in " + type + " " + name + ";\n";
}

void agl::ShaderBuilder::addIn(std::string type, std::string name)
{
	in += "in " + type + " " + name + ";\n";
}

void agl::ShaderBuilder::addOut(std::string type, std::string name)
{
	out += "out " + type + " " + name + ";\n";
}

void agl::ShaderBuilder::addUniform(std::string type, std::string name)
{
	uniform += "uniform " + type + " " + name + ";\n";
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
	this->addLayout(0, agl::vec3, "position");
	this->addLayout(1, agl::vec2, "vertexUV");

	this->addUniform(agl::mat4, "transform");
	this->addUniform(agl::mat4, "mvp");
	this->addUniform(agl::vec3, "shapeColor");
	this->addUniform(agl::mat4, "textureTransform");

	this->addOut(agl::vec2, "UVcoord");
	this->addOut(agl::vec4, "fragColor");

	this->setMain({
		agl::val("UVcoord")		= agl::val("vec2((textureTransform") * agl::val("vec4(vertexUV, 1, 1)).xy)"), //
		agl::val("fragColor")	= agl::val("vec4(shapeColor, 1)"),											  //
		agl::val("gl_Position") = agl::val("mvp") * agl::val("transform") * agl::val("vec4(position, 1)"),	  //
	});
}

void agl::ShaderBuilder::setDefaultFrag()
{
	this->addIn(agl::vec2, "UVcoord");
	this->addIn(agl::vec4, "fragColor");

	this->addOut(agl::vec4, "color");

	this->addUniform(agl::sampler2D, "myTextureSampler");

	this->setMain({
		agl::val("color") = agl::val("fragColor") * agl::val("texture(myTextureSampler, UVcoord)"), //
	});
}

std::string agl::ShaderBuilder::getSrc()
{
	return "#version 330 core\n" + layout + in + out + uniform + main;
}
