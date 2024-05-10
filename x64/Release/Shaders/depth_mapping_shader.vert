#version 460 core

layout (location = 0) in vec3 obj_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection_ortho;

void main()
{
    gl_Position = projection_ortho * view * (model * vec4(obj_pos, 1.0));
}