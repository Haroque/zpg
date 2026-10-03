/*
 * Antonin Harok HAR0199
 *
 * File: ShaderProgram.cpp
 * Description:  Implementation file for the ShaderProgram class
 */

#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
	: vertexShader_(std::move(vertexShader)),
	  fragmentShader_(std::move(fragmentShader))
{
	setShaderProgram();
}


bool ShaderProgram::setShaderProgram()

{
	if (id)
		glDeleteProgram(id);

	id = glCreateProgram();
	glAttachShader(id, vertexShader_.id());
	glAttachShader(id, fragmentShader_.id());
	glLinkProgram(id);

	GLint success = GL_FALSE;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		char infoLog[1024] = {};
		glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "Shader program linking failed: " << infoLog << '\n';
		glDeleteProgram(id);
		id = 0;
		return false;
	}
	return true;
}

ShaderProgram::~ShaderProgram()
{
	if (id)
		glDeleteProgram(id);
}

void ShaderProgram::use() const
{ 
	glUseProgram(id); 
}

