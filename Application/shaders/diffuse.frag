#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 ambientLight;

void main()
{
vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);

    // Ambient
    vec3 ambient = ambientLight * vertexColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * vertexColor;

    fragColor = vec4(ambient + diffuse, 1.0);
}