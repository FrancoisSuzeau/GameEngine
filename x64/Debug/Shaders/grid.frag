#version 460 core

uniform vec4 background_color;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
uniform bool bloom;

void main()
{

    // for bloom effect
    if(bloom)
    {
        vec3 lightColor = vec3(0.5f);
        vec3 objectColor = vec3(background_color.x, background_color.y, background_color.z) * lightColor;
        float brightness = dot(objectColor, vec3(0.2126, 0.7152, 0.0722));
        if(brightness > 0.0)
        {
            BrightColor = vec4(objectColor, 1.0);
        }
        else
        {
            BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
    else
    {
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }

    // Send result to backbuffer color
    FragColor = background_color;
    
}