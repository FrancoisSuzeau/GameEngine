#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 TexCoords;

struct Component
{
    samplerCube texture0;
};

uniform Component component;

uniform bool render_skybox;

void main()
{    

    vec3 objectColor = vec3(0.07f, 0.13f, 0.17f);
    if(render_skybox)
    {
        objectColor = texture(component.texture0, TexCoords).rgb;
    }
    FragColor = vec4(objectColor, 1.0);
    float brightness = dot(objectColor, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 2.0)
        BrightColor = vec4(objectColor, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}