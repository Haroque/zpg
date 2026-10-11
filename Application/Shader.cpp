/*
 * Antonin Harok HAR0199
 *
 * File: Shader.cpp
 * Description:  Implementation file for the Shader class
 */

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

Shader::Shader(GLenum type, const char* filePath)
	: id_(0)
{
	std::ifstream file(filePath);
	if (!file.is_open())
		throw std::runtime_error(std::string("Unable to open shader file: ") + filePath);

	std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string source = buffer.str();
    const char* sourcePointer = source.c_str();

	// Compile the shader source code,   but after making sure it exists
	id_ = glCreateShader(type);
    glShaderSource(id_, 1, &sourcePointer, nullptr);
	glCompileShader(id_);

	// Check specialization/compilation status
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

GLuint Shader::id() const { return id_; }