#version 460 core
layout (location = 0) in vec3 obj_pos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = obj_pos;
    gl_Position = projection * view * vec4(obj_pos, 1.0);
}  