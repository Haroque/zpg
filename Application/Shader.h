#pragma once

#include <glad/gl.h>

class Shader
{
public:
	Shader(GLenum type, const char* filePath);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	GLuint id() const;

private:
	GLuint id_ = 0;
};
