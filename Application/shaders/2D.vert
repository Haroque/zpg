#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 cn; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main()
{
    vec4 wp = modelMatrix * vec4(vp, 1.0);
    worldPosition = wp.xyz / wp.w;
    worldNormal = mat3(modelMatrix) * cn;

    vertexColor = cn; 

    gl_Position = projectionMatrix * viewMatrix * wp;
}