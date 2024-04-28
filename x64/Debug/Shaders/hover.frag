#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform bool render_line;
uniform bool bloom;
void main()
{
    // for bloom effect
    
    vec3 whiteColor = vec3(1.f);
    float alpha = 0.f;
    if(render_line)
    {
        alpha = 0.2f;
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