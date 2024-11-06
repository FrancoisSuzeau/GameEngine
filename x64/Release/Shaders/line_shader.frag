#version 450 core

layout (location = 0) out vec4 FragColor;

flat in vec4 line_color;

void main()
{
    FragColor = line_color;
    
}