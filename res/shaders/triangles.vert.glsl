#version 450 core

layout (location = 0) in vec3 position;

out vec4 vColor;

uniform mat4 mvMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * mvMat * vec4(position, 1.0);
    vColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}