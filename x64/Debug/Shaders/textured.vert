#version 450 core
layout (location = 0) in vec3 obj_pos;
layout (location = 2) in vec2 texture_coord;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = texture_coord;
    gl_Position = projection * view * ( model * vec4(obj_pos, 1.0));
}  