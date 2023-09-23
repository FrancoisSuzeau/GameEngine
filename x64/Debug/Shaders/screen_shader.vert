#version 460 core

layout (location = 0) in vec2 obj_pos;
layout (location = 1) in vec2 texture_coord;

out vec2 TexCoords;

void main()
{
    TexCoords = texture_coord;
    gl_Position = vec4(obj_pos.x, obj_pos.y, 0.0, 1.0);
    
}