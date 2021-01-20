#shader vertex
#version 330 core

layout(location = 0) in vec3 iv_Position;
layout(location = 1) in vec2 iv_Texture;
layout(location = 2) in vec3 iv_Color;

out vec3 ov_Color;
out vec2 ov_Texture;
void main()
{
    gl_Position = vec4(iv_Position, 1.0f);
    ov_Texture = iv_Texture;
    ov_Color = iv_Color;
}

#shader fragment
#version 330 core

in vec2 ov_Texture;
in vec3 ov_Color;
out vec4 of_Color;

uniform sampler2D u_Texture;

void main()
{
  of_Color = texture(u_Texture, ov_Texture) * vec4(ov_Color, 1.0f);
}