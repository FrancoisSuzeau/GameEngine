#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform bool render_line;

void main()
{
    // for bloom effect
    vec3 lightColor = vec3(3.f);
    vec3 whiteColor = vec3(1.f);
    whiteColor *= lightColor;
    
    FragColor = vec4(whiteColor, render_line);
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.0)
    {   
        BrightColor = FragColor;
    }  
	else
    {
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }

    // Send result to backbuffer color
    

    
}