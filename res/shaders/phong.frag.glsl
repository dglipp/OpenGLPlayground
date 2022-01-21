#version 450

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNorm;

in vec3 normal;
in vec3 vertexPos;
in vec3 lightDir;

out vec4 vColor;

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
    vec4 color;

    vec3 l = normalize(lightDir); // light vector from vertex to light
    vec3 n = normalize(normal);
    vec3 v = normalize(-vertexPos); // view vector
    vec3 r = reflect(-l, n); // reflection vector

    vec3 ambient = (globalAmbient * material.ambient + light.ambient * material.ambient).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(n, l), 0.0f);
    vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(dot(r, v), 0.0f), material.shininess);

    vColor = vec4(ambient + diffuse + specular, 1.0f);

}