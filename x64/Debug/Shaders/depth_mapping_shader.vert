#version 450 core

layout (location = 0) in vec3 obj_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * (model * vec4(obj_pos, 1.0));
}