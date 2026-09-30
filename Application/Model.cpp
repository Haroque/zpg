#include "Model.h"


Model::Model(const std::vector<float>& vertices, int vertexCount, GLenum drawMode)
    : vertexCount_(vertexCount), drawMode_(drawMode) // Uložíme si počet vrcholů pro pozdější volání draw
{
    glGenBuffers(1, &vertexBufferObject_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
    
    // Místo statického sizeof(points) spočítáme dynamickou velikost vektoru v bajtech
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
	glBindVertexArray(0); // Odpojení VAO po vykreslení (volitelné, ale dobrá praxe)
}