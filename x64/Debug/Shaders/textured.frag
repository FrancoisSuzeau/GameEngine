#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


in VS_OUT 
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;

} fs_in;

struct Component
{
    bool mixe_texture_color;
    bool is_light_source;
    float ambiant_strength;
    int specular_shininess;
    float specular_strength;
    vec4 background_color;
    sampler2D texture0;
};

uniform Component component;

struct Light 
{
    vec3 position;
    vec4 inner_color;
    bool is_textured;
    bool mixe_texture_color;
    sampler2D texture;
};

uniform Light src_light;

uniform bool there_is_light;
uniform vec3 camera_pos;

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

vec4 CalculateBrightColor(vec4 frag_color, float brightness_limit)
{
    float brightness = dot(frag_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > brightness_limit)
    {
        return vec4(frag_color.rgb, 1.0);
    }
    else
    {
        return vec4(0.0, 0.0, 0.0, 1.0);
    }
}

void main()
{    
    //Extract texture into fragment
    vec4 objectTexture = texture(component.texture0, fs_in.TexCoords);

    //Case if the fragment is part of a light source object
    if(component.is_light_source)
    {
        //Pass to framebuffer 0 (normal output)
        FragColor = GetMixedColor(objectTexture, component.background_color, component.mixe_texture_color);

        //Pass to framebuffer color 1 (bright output)
        BrightColor = CalculateBrightColor(FragColor, 0.f);
    }
    //Case if the fragment is not part of a light source object -> calculate complex object light effect
    else
    {
        if(there_is_light)
        {   
            vec3 light_color = src_light.inner_color.rgb;
            if(src_light.is_textured)
            {
                vec4 light_fragment = texture(src_light.texture, vec2(1.f));
                light_color = GetMixedColor(light_fragment, src_light.inner_color, src_light.mixe_texture_color).rgb;
            }

            //Ambiant
            vec3 ambiant = component.ambiant_strength * light_color;
            
            //Diffuse
            vec3 norm = normalize(fs_in.Normal);
            vec3 light_dir = normalize(src_light.position - fs_in.FragPos);
            float diff = max(dot(norm, light_dir), 0.f);
            vec3 diffuse = diff * light_color;

            //Specular
            vec3 view_dir = normalize(camera_pos - fs_in.FragPos);
            vec3 reflect_dir = reflect(-light_dir, norm);  
            float spec = pow(max(dot(view_dir, reflect_dir), 0.0), component.specular_shininess);
            vec3 specular = component.specular_strength * spec * light_color;  

            //Pass to framebuffer 0 (normal output)
            vec4 result = GetMixedColor(objectTexture, component.background_color, component.mixe_texture_color);
            vec3 final_result = (ambiant + diffuse + specular) * result.rgb;
            FragColor = vec4(final_result, result.a);

            //Pass to framebuffer color 1 (bright output)
            BrightColor = CalculateBrightColor(FragColor, 1.f);
        }
        else
        {
            //Pass to framebuffer 0 (normal output)
            FragColor = GetMixedColor(objectTexture, component.background_color, component.mixe_texture_color);

            //Pass to framebuffer color 1 (bright output)
            BrightColor = CalculateBrightColor(FragColor, 1.f);
        }
    }
    
    
}