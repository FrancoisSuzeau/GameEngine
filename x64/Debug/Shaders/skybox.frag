#version 460 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube texture0;

void main()
{    

    vec3 objectColor = texture(texture0, TexCoords).rgb;
    FragColor = vec4(objectColor, 1.0);
}