#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;            
layout (location = 2) in vec3 vertexColorIn; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float secAngle;
uniform float minAngle;
uniform float hourAngle;

out vec3 vertexColor;

mat4 getZRotation(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return mat4(
         c,  s, 0.0, 0.0,
        -s,  c, 0.0, 0.0,
       0.0, 0.0, 1.0, 0.0,
       0.0, 0.0, 0.0, 1.0
    );
}

void main()
{
    vec4 localPos = vec4(vp, 1.0);

    // 1. Minutes - green
    if (vertexColorIn.g > 0.5 && vertexColorIn.r < 0.3 && vertexColorIn.b < 0.3)
    {
        localPos = getZRotation(minAngle) * localPos;
        vertexColor = vec3(0.0, 0.0, 0.0);
    }
    // 2. Hour - blue

    else if (vertexColorIn.b > 0.5 && vertexColorIn.r < 0.3 && vertexColorIn.g < 0.3)
    {
        localPos = getZRotation(hourAngle) * localPos;
        vertexColor = vec3(0.0, 0.0, 0.0);
    }
    // 3. Second - red
    else if (vertexColorIn.r > 0.5 && vertexColorIn.g < 0.3 && vertexColorIn.b < 0.3)
    {
        localPos = getZRotation(secAngle) * localPos;
        vertexColor = vertexColorIn;
    }
    // 4. Watch face and backround do not rotate 
    else
    {
        vertexColor = vertexColorIn;
    }

    vec4 wp = modelMatrix * localPos;
    gl_Position = projectionMatrix * viewMatrix * wp;
}