#include "Shader.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

Shader::Shader(GLenum type, const char* filePath)
	: id_(glCreateShader(type))
{
	std::ifstream file(filePath);
	if (!file.is_open())
		throw std::runtime_error(std::string("Unable to open shader file: ") + filePath);

	const std::string source(std::istreambuf_iterator<char>(file), {});
	const char* sourcePointer = source.c_str();
	glShaderSource(id_, 1, &sourcePointer, nullptr);
	glCompileShader(id_);

	GLint success = GL_FALSE;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024] = {};
		glGetShaderInfoLog(id_, sizeof(infoLog), nullptr, infoLog);
		glDeleteShader(id_);
		id_ = 0;
		throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
	}
}

Shader::~Shader()
{
	if (id_)
		glDeleteShader(id_);
}

Shader::Shader(Shader&& other) noexcept
	: id_(other.id_)
{
	other.id_ = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		if (id_)
			glDeleteShader(id_);
		id_ = other.id_;
		other.id_ = 0;
	}
	return *this;
}

GLuint Shader::id() const { return id_; }
