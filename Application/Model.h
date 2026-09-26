#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model();
	~Model();

	//Model(const Model&) = delete;
	//Model& operator=(const Model&) = delete;

	void draw() const;

private:
	GLuint vertexArrayObject_ = 0;
	GLuint vertexBufferObject_ = 0;
};

