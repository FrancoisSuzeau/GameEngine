#version 450 core

uniform vec4 background_color;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
uniform bool is_light_source;
uniform bool there_is_light;
uniform float ambiant_strength;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 camera_pos;

in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
} fs_in;

void main()
{
    if(there_is_light)
    {
        //Ambiant
        vec3 ambiant = ambiant_strength * light_color;
        
        //Diffuse
        vec3 norm = normalize(fs_in.Normal);
        vec3 light_dir = normalize(light_pos - fs_in.FragPos);
        float diff = max(dot(light_dir, norm), 0.f);
        vec3 diffuse = diff * light_color;

        //Specular
        float specular_strength = 0.5;
        vec3 view_dir = normalize(camera_pos - fs_in.FragPos);
        vec3 reflect_dir = reflect(-light_dir, norm);  
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
        vec3 specular = specular_strength * spec * light_color;  

        //Pass to framebuffer color 0 (normal output)
        vec3 result = (ambiant + diffuse + specular) * background_color.rgb;
        FragColor = vec4(result, background_color.a);

        //Pass to framebuffer color 1 (bright output)
        float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
        float is_light_source_f = is_light_source ? 0.f : 1.f;
        if(brightness > is_light_source_f)
        {
            BrightColor = vec4(FragColor.rgb, 1.0);
        }
        else
        {
            BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
        
    }
    else
    {
        FragColor = background_color;
    }
}
