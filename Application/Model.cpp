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
    GLsizei stride = perVertexSize * sizeof(float);

	// 1. position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    if (perVertexSize == 6)
    {
        // 2. normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

		//Default color attribute (white) for models without color data
        glDisableVertexAttribArray(2);
        glVertexAttrib3f(2, 1.0f, 1.0f, 1.0f); 
    }
    else if (perVertexSize >= 9)
    {
		//If the length is approximately 1, it's likely a normal; if it's not, it's likely a color.
		// count the length squared of the vector at offset 3, 4, 5
        float lenSq = vertices[3] * vertices[3] + vertices[4] * vertices[4] + vertices[5] * vertices[5];
		bool hasNormalFirst = (lenSq > 0.8f && lenSq < 1.2f);

		// Set offsets based on the order of normal and color attributes
        int normalOffset = hasNormalFirst ? 3 : 6;
        int colorOffset = hasNormalFirst ? 6 : 3;

        // 1: normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(normalOffset * sizeof(float)));

        // 2: color
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(colorOffset * sizeof(float)));
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