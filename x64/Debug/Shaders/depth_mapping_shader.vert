#version 450 core

layout (location = 0) in vec3 obj_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection_ortho;

uniform bool is_light_source;

void main()
{
    gl_Position = projection_ortho * view * (model * vec4(obj_pos, 1.0));
}