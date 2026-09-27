#pragma once

#include <vector>

#include <glad/gl.h>

class Model
{
public:
	Model(const std::vector<float>& vertices, int vertexCount);
    ~Model();

	void draw() const;

private:
	GLuint vertexArrayObject_ = 0;
	GLuint vertexBufferObject_ = 0;
	int vertexCount_;
};