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
	
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;

	GLuint getId() const { return id; }

private:
	GLint uniformLocation(const std::string& name) const;
	GLuint id = 0;

	Shader vertexShader_;
	Shader fragmentShader_;
};