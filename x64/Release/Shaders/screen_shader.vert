#version 450 core

layout (location = 0) in vec3 obj_pos;
layout (location = 2) in vec2 texture_coord;

out vec2 TexCoords;

void main()
{
    TexCoords = texture_coord;
    gl_Position = vec4(obj_pos, 1.0);
    
}