#version 330 core

in vec3 worldNormal;
in vec3 vertexColor;

out vec4 fragColor;

void main()
{
    //from 3 to 9 
    float brightness = 0.6 + 0.3 * normalize(worldNormal).y;

    fragColor = vec4(vertexColor * brightness, 1.0);
}