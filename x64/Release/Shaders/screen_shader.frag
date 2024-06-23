#version 450 core

out vec4 FragColor;
in vec2 TexCoords;

struct Component
{
    sampler2D texture0;
    sampler2D texture1;
};

uniform Component component;

uniform bool bloom;

void main()
{
    if(bloom)
    {
        vec4 texture0_extract = texture(component.texture0, TexCoords);
        vec4 texture1_extract = texture(component.texture1, TexCoords);
        texture0_extract += texture1_extract;
        FragColor = texture0_extract;
    }
    else
    {
        FragColor = texture(component.texture0, TexCoords);
    }
}