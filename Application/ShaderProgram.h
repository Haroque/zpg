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

private:
	GLuint id = 0;

	Shader vertexShader_;
	Shader fragmentShader_;
};