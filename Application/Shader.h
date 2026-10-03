/*
 * Antonin Harok HAR0199
 *
 * File: Shader.h
 * Description:  Header file for the Shader class
 */
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
