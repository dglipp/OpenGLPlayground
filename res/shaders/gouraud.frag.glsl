#version 450

in vec4 vColor;
out vec4 fColor;

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
    fColor = vColor;
}