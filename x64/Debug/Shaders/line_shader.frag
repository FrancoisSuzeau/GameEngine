#version 450 core

layout (location = 0) out vec4 FragColor;

flat in vec4 line_color;

// struct Component
// {
//     vec4 background_color;
// };

// uniform Component component;


void main()
{
    FragColor = line_color;
    
}