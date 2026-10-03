#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

uniform vec3 Translation;
uniform vec3 Scale;
uniform float Rotation; //The angle in which the object is rotating

out vec3 vertexColor;

void main()
{
    //A = [x, y, z]
    float x = Position.x * Scale.x;
    float y = Position.y * Scale.y; 
    float z = Position.z * Scale.z;

    //goniometric func for angle alpha
    float cosA = cos(Rotation); 
    float sinA = sin(Rotation);


    float posX =  cosA * x + sinA * z;
    float posY =  y;
    float posZ = -sinA * x + cosA * z;

    //translation
    float translationX = posX + Translation.x;
    float translationY = posY + Translation.y;
    float translationZ = posZ + Translation.z;

    vertexColor = Normal;
    gl_Position = vec4(translationX, translationY, translationZ, 1.0);
}