#version 450 core
layout (location = 0) in vec3 obj_pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec3 frag_pos = vec3(model * vec4(obj_pos, 1.0));
    gl_Position = projection * view * vec4(frag_pos, 1.0);
}  