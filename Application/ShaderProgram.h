#pragma once

#include <glad/gl.h>

#include "Shader.h"
#include "Transformation.h"

class ShaderProgram
{
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();


	bool setShaderProgram();
	void use() const;
	void setTransformation(const Transformation& transformation) const;

private:
	GLuint id = 0;

	Shader vertexShader_;
	Shader fragmentShader_;
};