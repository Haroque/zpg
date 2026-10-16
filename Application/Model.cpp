/*
 * Antonin Harok HAR0199
 *
 * File: Model.cpp
 * Description:  Implementation file for the Model class
 */

#include "Model.h"


Model::Model(const std::vector<float>& vertices, int vertexCount, GLenum drawMode)
	: vertexCount_(vertexCount), drawMode_(drawMode) //  Saving the vertex count for later draw calls
{
    if (vertexCount_ <= 0 || vertices.empty())
        return;

    glGenVertexArrays(1, &vertexArrayObject_);//creating and bindind a vao
    glBindVertexArray(vertexArrayObject_);

    glGenBuffers(1, &vertexBufferObject_); 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	int perVertexSize = static_cast<int>(vertices.size() / vertexCount_);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, perVertexSize * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, perVertexSize * sizeof(float), (void*)(3 * sizeof(float)));

    if (perVertexSize >= 9)
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, perVertexSize * sizeof(float), (void*)(6 * sizeof(float)));
    }

	glBindVertexArray(0); 
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