#shader vertex
#version 330 core

layout(location = 0) in vec3 iv_Position;
layout(location = 1) in vec3 iv_Color;

out vec3 ov_Color;

void main()
{
    gl_Position = vec4(iv_Position, 1.0f);
    ov_Color = iv_Color;
}

#shader fragment
#version 330 core

in vec3 ov_Color;
out vec4 of_Color;

void main()
{
  of_Color = vec4(ov_Color, 1.0f);
}