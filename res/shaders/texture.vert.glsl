#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 tc;

uniform mat4 mvMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * mvMat * vec4(position, 1.0);
    tc = texCoord;
}