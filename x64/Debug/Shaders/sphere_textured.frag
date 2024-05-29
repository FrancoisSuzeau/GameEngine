#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec4 background_color;
in vec3 TexCoords;
uniform bool mixe_texture_color;
uniform bool is_light_source;
uniform bool there_is_light;
uniform float ambiant_strength;
uniform int specular_shininess;

in VS_OUT 
{
    vec3 Normal;
    vec3 FragPos;
    vec3 TexCoords;

} fs_in;

uniform vec3 light_source_position;
uniform vec4 light_source_inner_color;
uniform vec3 camera_pos;
uniform bool is_light_source_textured;
uniform bool light_src_mixe_texture_color;



uniform sampler2D texture0;
uniform sampler2D light_src_texture;


vec4 GetMixedColor(vec4 object_texture, vec4 color, bool mixe)
{
    if(mixe)
    {
        return vec4(mix(object_texture.rgb, color.rgb, color.a) * object_texture.a, 1.0);
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
        FragColor = GetMixedColor(objectTexture, background_color, mixe_texture_color);
    
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
            vec3 light_color = light_source_inner_color.rgb;
            if(is_light_source_textured)
            {
                vec4 light_fragment = texture(light_src_texture, vec2(1.f));
                light_color = GetMixedColor(light_fragment, light_source_inner_color, light_src_mixe_texture_color).rgb;
            }

            //Ambiant
            vec3 ambiant = ambiant_strength * light_color;
            
            //Diffuse
            vec3 norm = normalize(fs_in.Normal);
            vec3 light_dir = normalize(light_source_position - fs_in.FragPos);
            float diff = max(dot(norm, light_dir), 0.f);
            vec3 diffuse = diff * light_color;

            //Specular
            float specular_strength = 0.5;
            vec3 view_dir = normalize(camera_pos - fs_in.FragPos);
            vec3 reflect_dir = reflect(-light_dir, norm);  
            float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_shininess);
            vec3 specular = specular_strength * spec * light_color;  

            //Pass to framebuffer 0 (normal output)
            vec4 result = GetMixedColor(objectTexture, background_color, mixe_texture_color);
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
            FragColor = GetMixedColor(objectTexture, background_color, mixe_texture_color);

        }
        
    }
    
}