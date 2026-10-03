/*
 * Antonin Harok HAR0199
 *
 * File: ShaderProgram.h
 * Description:  Header file for the ShaderProgram class
 */

#pragma once
#include <glad/gl.h>
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();


	bool setShaderProgram();
	void use() const;

	GLuint getId() const { return id; }

private:
	GLuint id = 0;

	Shader vertexShader_;
	Shader fragmentShader_;
};