#version 450

layout (location = 0) in vec3 position;

// Uniforms
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float tf;
uniform vec3 rotParams;

out vec4 vColor;

// utility functions
mat4 buildRotX(float rad);
mat4 buildRotY(float rad);
mat4 buildRotZ(float rad);

mat4 buildTranslate(float x, float y, float z);

void main()
{
    float i = gl_InstanceID + tf;
    float b = i / rotParams[1] * 10000 - 10000;
    float a = sin(i * 2030.0 / rotParams[0]) * i / 50;
    float c = sin(i * 2030.0 / rotParams[2]) * i / 50;

    mat4 localRotX = buildRotX(1 * i);
    mat4 localRotY = buildRotY(1 * i);
    mat4 localRotZ = buildRotZ(1 * i);
    mat4 localTrans = buildTranslate(a, b, c);

    mat4 modelMatrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mvMatrix = viewMatrix * modelMatrix;

    gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
    vColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5); 
}


mat4 buildTranslate(float x, float y, float z)
{
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x, y, z, 1.0);
    
    return trans;
}

mat4 buildRotX(float rad)
{
    mat4 rot = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, cos(rad), -sin(rad), 0.0,
                    0.0, sin(rad), cos(rad), 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    return rot;
}

mat4 buildRotY(float rad)
{
    mat4 rot = mat4(cos(rad), 0.0, sin(rad), 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    -sin(rad), 0.0, cos(rad), 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    return rot;
}

mat4 buildRotZ(float rad)
{
    mat4 rot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                    sin(rad), cos(rad), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    return rot;
}

mat4 buildScale(float x, float y, float z)
{
    mat4 scale = mat4(x, 0.0, 0.0, 0.0,
                      0.0, y, 0.0, 0.0,
                      0.0, 0.0, z, 0.0, 
                      0.0, 0.0, 0.0, 1.0);

    return scale;
}