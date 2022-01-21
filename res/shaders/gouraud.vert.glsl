#version 450

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNorm;

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

    vec4 p = mvMat * vec4(vertPos, 1.0f); // vertex position vector
    vec3 n = normalize((normMat * vec4(vertNorm, 1.0f)).xyz); // normal vector
    vec3 l = normalize(light.position - p.xyz); // light vector from vertex to light

    vec3 v = normalize(-p.xyz); // view vector
    vec3 r = reflect(-l, n); // reflection vector

    vec3 ambient = (globalAmbient * material.ambient + light.ambient * material.ambient).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(n, l), 0.0f);
    vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(dot(r, v), 0.0f), material.shininess);

    vColor = vec4(ambient + diffuse + specular, 1.0f);

    gl_Position = projMat * mvMat * vec4(vertPos, 1.0f);
}