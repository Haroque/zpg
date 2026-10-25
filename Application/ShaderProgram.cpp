/*
 * Antonin Harok HAR0199
 *
 * File: ShaderProgram.cpp
 * Description:  Implementation file for the ShaderProgram class
 */

#include "ShaderProgram.h"
#include "Camera.h"
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

GLint ShaderProgram::uniformLocation(const GLchar* name) const
{
	GLint location = glGetUniformLocation(id, name);
	return location;
}

void ShaderProgram::setUniform(const GLchar* name, float value) const
{
	GLint location = uniformLocation(name);
	if (location != -1)
		glUniform1f(location, value);
}

void ShaderProgram::setUniform(const GLchar* name, int value) const
{
	GLint location = uniformLocation(name);
	if (location != -1)
		glUniform1i(location, value);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec3& value) const
{
	GLint location = uniformLocation(name);
	if (location != -1)
		glUniform3fv(location, 1, glm::value_ptr(value));
}

//new uniform function without transponing the matrix
// glm::value_ptr returns a pointer to the first element of the matrix in columns
void ShaderProgram::setUniform(const GLchar* name, const glm::mat4 matrix) const
{
	GLint location = uniformLocation(name);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setCamera(const Camera* camera)
{
	camera_ = camera;
	if (camera)
		notify();
}

void ShaderProgram::notify()
{
	if (camera_ && id != 0)
	{
		use();
		setUniform("viewMatrix", camera_->getViewMatrix());
		setUniform("projectionMatrix", camera_->getProjectionMatrix());
		setUniform("cameraPosition", camera_->getEye());
	}
}