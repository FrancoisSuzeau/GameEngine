#version 460 core

uniform vec3 background_color;
out vec4 FragColor;
uniform bool render_line;

void main()
{
    vec4 color = vec4(background_color, 1.f);
    if(render_line)
    {
        color = vec4(1.f);
    }

    FragColor = color;
    
}