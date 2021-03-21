#shader vertex
#version 330 core

layout(location = 0) in vec3 iv_Position;
layout(location = 1) in vec3 iv_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 if_Normal;
out vec3 if_FragmentPosition;

void main()
{
    if_Normal = iv_Normal;
    if_FragmentPosition = vec3(u_Model * vec4(iv_Position, 1.0));
    gl_Position = u_Projection * u_View * u_Model * vec4(iv_Position, 1.0);
}

#shader fragment
#version 330 core

in vec3 if_Normal;
in vec3 if_FragmentPosition;

uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightPosition;

out vec4 of_Color;

void main()
{
  // AMBIENT LIGHT
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * u_LightColor;

  // DIFFUSIVE LIGHT
  vec3 normal = normalize(if_Normal);
  vec3 lightDirection = normalize(u_LightPosition - if_FragmentPosition);
  float diff = 0.25 * max(dot(normal, lightDirection), 0.0);
  vec3 diffusive = diff * u_LightColor;

  of_Color = vec4(u_ObjectColor * (ambient + diffusive), 1.0);

}