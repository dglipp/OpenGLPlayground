#shader vertex
#version 330 core

layout(location = 0) in vec3 iv_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(iv_Position, 1.0);
}

#shader fragment
#version 330 core

out vec4 of_Color;
uniform vec3 u_LightColor;

void main()
{
  of_Color = vec4(u_LightColor, 1.0);
}