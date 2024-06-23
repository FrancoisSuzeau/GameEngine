#version 450 core
layout (location = 0) in vec3 obj_pos;
layout (location = 1) in vec3 obj_normals;
layout (location = 2) in vec3 texture_coord;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT 
{
    vec3 Normal;
    vec3 FragPos;
    vec3 TexCoords;

} vs_out;

void main()
{
    vs_out.TexCoords = texture_coord;
    vs_out.FragPos = vec3(model * vec4(obj_pos, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));
    vs_out.Normal = normalMatrice * obj_normals;
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}  