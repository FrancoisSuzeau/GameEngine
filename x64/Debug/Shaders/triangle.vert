#version 460 core

layout (location = 0) in vec3 obj_pos;

void main()
{
    gl_Position = vec4(obj_pos, 1.0);
}