#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool bloom;

void main()
{
   

    if(bloom)
    {
        vec3 texture0_extract = texture(texture0, TexCoords).rgb;
        vec3 texture1_extract = texture(texture1, TexCoords).rgb;
        texture0_extract += texture1_extract;
        FragColor = vec4(texture0_extract, 1.0);
    }
    else
    {
        vec3 color = texture(texture0, TexCoords).rgb;
        FragColor = vec4(color, 1.0);
    }

    


}