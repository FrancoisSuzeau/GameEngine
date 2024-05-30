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
        vec3 texture0_extract = texture(component.texture0, TexCoords).rgb;
        vec3 texture1_extract = texture(component.texture1, TexCoords).rgb;
        texture0_extract += texture1_extract;
        FragColor = vec4(texture0_extract, 1.f);
    }
    else
    {
        vec3 color = texture(component.texture0, TexCoords).rgb;
        FragColor = vec4(color, 1.0);
    }
}