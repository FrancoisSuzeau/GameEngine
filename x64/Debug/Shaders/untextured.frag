#version 450 core

#define MAX_LIGHTS 30

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct Component
{
    vec4 background_color;
    float ambiant_strength;
    int specular_shininess;
    float specular_strength;
    bool is_light_source;
    bool is_spot_light;
    vec3 direction;
    float intensity;
    float cut_off;

};

uniform Component component;

struct Light 
{
    vec3 position;
    float _padding1;
    vec4 inner_color;
    int is_textured;
    int mixe_texture_color;
    float constant;
    float linear;
    float quadratic;
    int is_point_light;
    int is_spot_light;
    int is_directional;
    vec3 direction;
    float _padding2;
    float cut_off;
    float outer_cut_off;
    int is_attenuation;
    float intensity;
    int texture_index;
    float _padding3[3];

};

layout(std430, binding = 0) buffer LightBlock {
    Light src_lights[];
} Lights;

uniform sampler2D light_textures[MAX_LIGHTS];

uniform bool there_is_light;
uniform vec3 camera_pos;
uniform int light_sources_count;

in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
} fs_in;

vec4 GetMixedColor(vec4 object_texture, vec4 color, int mixe)
{
    if(mixe == 1)
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

vec3 GetLightDir(int i)
{
    if(Lights.src_lights[i].is_directional == 1)
    {
        return normalize(Lights.src_lights[i].direction);
    }
    else
    {
        return normalize(Lights.src_lights[i].position - fs_in.FragPos);
    }
}

void main()
{
    
    //Case if the fragment is part of a light source object
    if(component.is_light_source)
    {
        vec3 color = component.background_color.rgb;
        if(component.is_spot_light)
        {
            //Ambiant
            vec3 ambiant = 0.f * color;

            //Diffuse
            vec3 norm = normalize(fs_in.Normal);
            vec3 light_dir = normalize(component.direction);
            float diff = max(dot(light_dir, norm), component.intensity);
            vec3 diffuse = diff * color;

            float theta = dot(light_dir, norm);
            if(theta > component.cut_off)
            {
                color = (ambiant + diffuse) * component.background_color.rgb;
            }
            else
            {
                color = ambiant * component.background_color.rgb;
            }
        }

        //Pass to framebuffer 0 (normal output)
        FragColor = vec4(color, component.background_color.a);

        //Pass to framebuffer 1 (bright output)
        BrightColor = CalculateBrightColor(FragColor, 0.f);
       
    }
    //Case if the fragment is not part of a light source object -> calculate complex object light effect
    else
    {
        if(there_is_light)
        {
            vec3 result = vec3(0.f);
            for(int i = 0; i < light_sources_count; i++)
            {
                vec3 light_color = Lights.src_lights[i].inner_color.rgb;
                if(Lights.src_lights[i].is_textured == 1 && Lights.src_lights[i].texture_index < MAX_LIGHTS)
                {
                    vec4 light_fragment = texture(light_textures[Lights.src_lights[i].texture_index], vec2(1.f));
                    light_color = GetMixedColor(light_fragment, Lights.src_lights[i].inner_color, Lights.src_lights[i].mixe_texture_color).rgb;
                }

                //Ambiant
                vec3 ambiant = component.ambiant_strength * light_color;
                
                //Diffuse
                vec3 norm = normalize(fs_in.Normal);
                vec3 light_dir = GetLightDir(i);
                float diff = max(dot(light_dir, norm), Lights.src_lights[i].intensity);
                vec3 diffuse = diff * light_color;

                //Specular
                vec3 view_dir = normalize(camera_pos - fs_in.FragPos);
                vec3 reflect_dir = reflect(-light_dir, norm);  
                float spec = pow(max(dot(view_dir, reflect_dir), 0.0), component.specular_shininess);
                vec3 specular = component.specular_strength * spec * light_color;

                //Attenuation
                float distance = length(Lights.src_lights[i].position - fs_in.FragPos);
                float attenuation = 1.0 / (Lights.src_lights[i].constant + Lights.src_lights[i].linear * distance + Lights.src_lights[i].quadratic * (distance * distance));
                if(Lights.src_lights[i].is_point_light == 1)
                {
                    ambiant *= attenuation;
                    diffuse *= attenuation;
                    specular *= attenuation;
                } 

                if(Lights.src_lights[i].is_spot_light == 1)
                {
                    if(Lights.src_lights[i].is_attenuation == 1)
                    {
                        diffuse *= attenuation;
                        specular *= attenuation;
                    }

                    float theta = dot(light_dir, normalize(-Lights.src_lights[i].direction));
                    float epsilon = (Lights.src_lights[i].cut_off - Lights.src_lights[i].outer_cut_off);
                    float intensity = clamp((theta - Lights.src_lights[i].outer_cut_off) / epsilon, 0.f, 1.f);
                    diffuse *= intensity;
                    specular *= intensity;
                }   

                //Pass to framebuffer 1 (bright output)
                result += (ambiant + diffuse + specular) * component.background_color.rgb;
            }
            FragColor = vec4(result, component.background_color.a);
            
            //Pass to framebuffer 1 (bright output)
            BrightColor = CalculateBrightColor(FragColor, 1.f);
            
        }
        else
        {
            //Pass to framebuffer 0 (normal output)
            FragColor = component.background_color;

            //Pass to framebuffer 1 (bright output)
            BrightColor = CalculateBrightColor(FragColor, 1.f);
        }
        
    }
    
}
