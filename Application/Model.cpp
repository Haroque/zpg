#include "Model.h"


Model::Model(const std::vector<float>& vertices, int vertexCount, GLenum drawMode)
	: vertexCount_(vertexCount), drawMode_(drawMode) //  Saving the vertex count for later draw calls
{
    glGenBuffers(1, &vertexBufferObject_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
    
	//Instead of static sizeof(points), calculates the dynamic size of the vector in bytes
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

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
	glDrawArrays(drawMode_, 0, vertexCount_);
	glBindVertexArray(0); //Setting vao to 0 unbinds the current vao, a good practice to avoid accidental modifications to it later in the code.
}