#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;


uniform mat4 modelMatrix;

out vec3 vertexColor;

void main()
{
    vertexColor = Normal;
    gl_Position = modelMatrix * vec4(Position, 1.0);
}