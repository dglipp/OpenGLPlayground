#version 450 core

layout (binding = 0) uniform sampler2D smp; 

in vec2 tc;
out vec4 fColor;

void main()
{
    fColor = texture(smp, tc);
}