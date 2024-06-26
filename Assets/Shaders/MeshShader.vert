#version 410 core

//Set Binding Point of Uniform Buffer directly in the shader file, feature available from OpenGL 4.2 onwards (Windows/Linux only)
//layout(binding = 0) uniform Data
layout (row_major) uniform Data //uniform buffer Data
{
    mat4 world;
    mat4 view;
    mat4 projection;
}; 


layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec2 outTexcoord;


void main(void)
{
    vec4 pos = vec4(position, 1) * world; //multiply the world matrix with the vertex position in order to obtain the final position
    pos = pos * view ; //multiply the view matrix with the world position in order to obtain the position in view space
    pos = pos * projection; //multiply the projection matrix with the view position in order to obtain the final position in screen space

    gl_Position = pos;

    outTexcoord = texcoord;
}