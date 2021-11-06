#version 450

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNorm;

out vec3 normal;
out vec3 lightDir;
out vec3 vertexPos; // in view space

struct pLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 globalAmbient;
uniform pLight light;
uniform Material material;
uniform mat4 mvMat;
uniform mat4 normMat;
uniform mat4 projMat;

void main()
{
    vertexPos = (mvMat * vec4(vertPos, 1.0)).xyz;
    lightDir = light.position - vertexPos;
    normal = (normMat * vec4(vertNorm, 1.0)).xyz;

    gl_Position = projMat * mvMat * vec4(vertPos, 1.0f);
}