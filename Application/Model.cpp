#include "Model.h"

Model::Model()
{
	const float points[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &vertexBufferObject_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArrayObject_);
	glBindVertexArray(vertexArrayObject_);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vertexArrayObject_);
	glDeleteBuffers(1, &vertexBufferObject_);
}

void Model::draw() const
{
	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
