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

std::string agl::ShaderBuilder::getSrc()
{
	return "#version 330 core\n" + layout + in + out + uniform + main;
}
