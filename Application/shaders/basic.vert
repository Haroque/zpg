#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform vec3 uPosition;
uniform float uRotationAngle;

void main()
{
    float cosA = cos(uRotationAngle);
    float sinA = sin(uRotationAngle);

    vec3 rotatedPos;
    rotatedPos.x = inPosition.x * cosA + inPosition.z * sinA;
    rotatedPos.y = inPosition.y;
    rotatedPos.z = -inPosition.x * sinA + inPosition.z * cosA;
    
    //vertexColor = color;

    gl_Position = vec4((rotatedPos + uPosition), 1.0);
}