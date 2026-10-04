/*
 * Antonin Harok HAR0199
 *
 * File: ShaderProgram.h
 * Description:  Header file for the ShaderProgram class
 */

#pragma once
#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <string>

#include "Shader.h"


class ShaderProgram
{
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();


	bool setShaderProgram();
	void use() const;
	
	void setUniform(const GLchar* name, float value) const; //rotation
	void setUniform(const GLchar* name, int value) const;
	void setUniform(const GLchar* name, const glm::vec3& value) const;

	GLint uniformLocation(const GLchar* name) const;
	GLuint getId() const { return id; }


private:
	GLuint id = 0;

	Shader vertexShader_;
	Shader fragmentShader_;
};