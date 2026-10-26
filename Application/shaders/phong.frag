#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 lightColor;


uniform vec3 ambientLight;
uniform float shininess;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    // 1. ambient part
    vec3 ambient = ambientLight * vertexColor;

    // 2. lambert part
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * vertexColor;

    // 3. phong
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}