#version 450 core
layout (location = 0) in vec3 obj_pos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = obj_pos;
    vec4 pos = projection * view * vec4(obj_pos, 1.0);
    gl_Position = pos.xyww;
}  