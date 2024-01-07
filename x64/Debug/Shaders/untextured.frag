#version 460 core

uniform vec3 background_color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(background_color, 1.f);
    
}