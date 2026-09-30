#pragma once

#include <glad/gl.h>

class Shader
{
public:
	Shader(GLenum type, const char* filePath);
	~Shader();


	GLuint id() const;

private:
	GLuint id_ = 0;
};
