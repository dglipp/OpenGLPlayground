#version 450 core

in vec4 vColor;
out vec4 fColor;

uniform mat4 mvMat;
uniform mat4 projMat;

void main()
{
    fColor = vColor;
}