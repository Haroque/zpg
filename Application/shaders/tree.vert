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

    //
    float rnd = sin(modelMatrix[3].x + modelMatrix[3].z);

    if (gl_VertexID > 36443)
        vertexColor = vec3(0.0, 1.0, 0.0); // green
    else
        vertexColor = vec3(0.35, 0.22, 0.19); // red/brown

    gl_Position = projectionMatrix * viewMatrix * wp;
}