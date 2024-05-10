#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool bloom;
// uniform float near_plane;
// uniform float far_plane;

// float LinearizeDepth(float depth)
// {
//     float near = near_plane * 10.f;
//     float far = far_plane / 10.f;
//     float z = depth * 2.0 - 1.0; // Back to NDC 
//     return (2.0 * near * far) / (far + near - z * (far - near));	
// }

void main()
{
    // float far = far_plane / 10.f;
    // float depthValue = texture(texture0, TexCoords).r;
    // FragColor = vec4(vec3(LinearizeDepth(depthValue) / far), 1.0); // perspective
    // //FragColor = vec4(vec3(depthValue), 1.0); // orthographic

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