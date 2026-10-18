#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 cn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float colorOffset = 1.0;

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main()
{
    vec4 wp = modelMatrix * vec4(vp, 1.0);
    worldPosition = wp.xyz / wp.w;
    worldNormal = mat3(modelMatrix) * cn;

    //3.x id position in matrix, frac return the decimal value 
    float variace = fract(abs(modelMatrix[3].x));
    float colorOffset = 0.7 + variace * 0.5; //from 0.7 to 1.2

    if (gl_VertexID > 36443)
        vertexColor = vec3(0.0, 1.0, 0.0) * colorOffset; // green
    else
        vertexColor = vec3(0.35, 0.22, 0.19) * colorOffset; // red/brown

    gl_Position = projectionMatrix * viewMatrix * wp;
}