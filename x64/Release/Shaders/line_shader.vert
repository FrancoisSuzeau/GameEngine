#version 450 core
layout (location = 0) in vec3 obj_pos;
layout (location = 3) in vec4 color_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

flat out vec4 line_color;

void main()
{
    vec3 frag_pos = vec3(model * vec4(obj_pos, 1.0));
    line_color = color_coord;
    gl_Position = projection * view * vec4(frag_pos, 1.0);
}  