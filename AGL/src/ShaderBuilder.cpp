#include "../include/ShaderBuilder.hpp"

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

std::string agl::ShaderBuilder::getSrc()
{
	return in + out + uniform + main;
}
