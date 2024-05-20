#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec4 background_color;
in vec3 TexCoords;
uniform bool mixe_texture_color;

uniform sampler2D texture0;

void main()
{    
    vec2 longitudeLatitude = vec2((atan(TexCoords.x, TexCoords.z) / 3.1415926 + 1.0) * 0.5,
                                  (asin(TexCoords.y) / 3.1415926 + 0.5));

    vec4 objectTexture = texture(texture0, longitudeLatitude);
    if(mixe_texture_color)
    {
        FragColor = vec4(mix(objectTexture.rgb, background_color.rgb, background_color.a) * objectTexture.a, 1.0);
    }
    else
    {
        FragColor = objectTexture;
    }
    
    float brightness = dot(objectTexture.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 2.0)
        BrightColor = vec4(objectTexture.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}