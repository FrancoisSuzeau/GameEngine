#version 450 core

layout (location = 0) out vec4 FragColor;


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
    sampler2D texture_normal1;
    sampler2D texture_specular1;
    sampler2D texture_diffuse1;
    sampler2D texture_height1;
    bool is_spot_light;
    vec3 direction;
    float intensity;
    float cut_off;
};

uniform Component component;


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
    //Extract texture into fragment
    vec4 objectTexture = texture(component.texture_diffuse1, fs_in.TexCoords);
    //Pass to framebuffer 0 (normal output)
    FragColor = GetMixedColor(objectTexture, component.background_color, component.mixe_texture_color);
    
}