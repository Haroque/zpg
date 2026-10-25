#version 330 core


in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

out vec4 fragColor;


uniform vec3 ambientLight;

void main()
{
    vec3 ambient = ambientLight * vertexColor;
    fragColor = vec4(ambient, 1.0);
}