#version 450 core

layout (location = 0) out vec4 FragColor;

struct Component
{
    vec4 background_color;
};

uniform Component component;


void main()
{
    FragColor = component.background_color;
    
}