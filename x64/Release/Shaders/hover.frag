#version 450 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


struct Component
{
    bool render_line;
    float alpha_strength;
};
uniform Component component;

uniform bool bloom;

void main()
{
    vec3 whiteColor = vec3(1.f);
    float alpha = 0.f;
    if(component.render_line)
    {
        alpha = component.alpha_strength;
    }
    if(bloom)
    {
        vec3 lightColor = vec3(3.f);
        whiteColor *= lightColor;
        
        vec4 result = vec4(whiteColor, alpha);
        float brightness = dot(result.rgb, vec3(0.2126, 0.7152, 0.0722));
        if(brightness > 0.0)
        {   
            BrightColor = result;
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
    FragColor = vec4(whiteColor, alpha);
    
}