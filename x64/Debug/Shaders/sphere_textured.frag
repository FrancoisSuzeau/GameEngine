#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec4 background_color;
in vec3 TexCoords;
uniform bool mixe_texture_color;
uniform bool is_light_source;
uniform bool there_is_light;
uniform float ambiant_strength;

in VS_OUT 
{
    vec3 Normal;
    vec3 FragPos;
    vec3 TexCoords;

} fs_in;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 camera_pos;

uniform sampler2D texture0;

vec4 GetMixedColor(vec4 object_texture)
{
    if(mixe_texture_color)
    {
        return vec4(mix(object_texture.rgb, background_color.rgb, background_color.a) * object_texture.a, 1.0);
    }
    else
    {
        return object_texture;
    }
}

void main()
{   
    //Calculate longitude-latitude position of the fragment 
    vec2 longitudeLatitude = vec2((atan(fs_in.TexCoords.x, fs_in.TexCoords.z) / 3.1415926 + 1.0) * 0.5,
                                  (asin(fs_in.TexCoords.y) / 3.1415926 + 0.5));

    //Extract texture into fragment
    vec4 objectTexture = texture(texture0, longitudeLatitude);

    //Case if the fragment is part of a light source object
    if(is_light_source)
    {
        FragColor = GetMixedColor(objectTexture);
    
        float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
        if(brightness > 0.f)
        {
            BrightColor = vec4(FragColor.rgb, 1.0);
        }
            
        else
        {
            BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
    //Case if the fragment is not part of a light source object -> calculate complex object light effect
    else
    {
        if(there_is_light)
        {
            //Ambiant
            vec3 ambiant = ambiant_strength * light_color;
            
            //Diffuse
            vec3 norm = normalize(fs_in.Normal);
            vec3 light_dir = normalize(light_pos - fs_in.FragPos);
            float diff = max(dot(norm, light_dir), 0.f);
            vec3 diffuse = diff * light_color;

            //Specular
            float specular_strength = 0.5;
            vec3 view_dir = normalize(camera_pos - fs_in.FragPos);
            vec3 reflect_dir = reflect(-light_dir, norm);  
            float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
            vec3 specular = specular_strength * spec * light_color;  

            //Pass to framebuffer 0 (normal output)
            vec4 result = GetMixedColor(objectTexture);
            vec3 final_result = (ambiant + diffuse + specular) * result.rgb;
            FragColor = vec4(final_result, result.a);
            
            //Pass to framebuffer color 1 (bright output)
            float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
            if(brightness > 1.f)
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
            FragColor = GetMixedColor(objectTexture);

        }
        
    }
    
}