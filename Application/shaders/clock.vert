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

void main()
{
    float angle = 0.0;
    vertexColor = vertexColorIn;

    // 1. Minutes - green
    if (vertexColorIn.g > 0.5 && vertexColorIn.r < 0.3)
    {
        angle = minAngle;
        vertexColor = vec3(0.0);
    }
    // 2. Hour - blue
    else if (vertexColorIn.b > 0.5 && vertexColorIn.r < 0.3)
    {
        angle = hourAngle;
        vertexColor = vec3(0.0);
    }
    // 3. Second - red
    else if (vertexColorIn.r > 0.5 && vertexColorIn.g < 0.3)
    {
        angle = secAngle;
    }
    else if (vertexColorIn.r > 0.5 && vertexColorIn.g > 0.5 && vertexColorIn.b < 0.3)
    {
        vertexColor = vec3(5.0 / 255.0, 195.0 / 255.0, 222.0 / 255.0);
    }
    //  Watch face and backround do not rotate 
    else
    {
        vertexColor = vertexColorIn;
    }

    //2D rotation in x and y, only if the hand is rotating
    vec3 pos = vp;
    if (angle != 0.0)
    {
        float c = cos(angle);
        float s = sin(angle);
        pos.xy = mat2(c, s, -s, c) * pos.xy;
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}