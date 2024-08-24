// // ============ GLSL version ============
// #version 400 core

// // ============ In data ============
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;
// uniform mat4 view;
// uniform mat4 model;
// uniform mat4 projection;

// // ============ Out data ============
// out vec2 TexCoords;
// out vec3 Normal;
// out vec3 FragPos;

// void main()
// {    
//     gl_Position = projection * view * (model * vec4(aPos, 1.0f));

//     TexCoords = aTexCoords;

//     Normal = mat3(transpose(inverse(model))) * aNormal;
//     FragPos = vec3(model * vec4(aPos, 1.0));
// }

#version 450 core
layout (location = 0) in vec3 obj_pos;
layout (location = 1) in vec3 obj_normals;
layout (location = 2) in vec2 texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT 
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;

} vs_out;

void main()
{
    vs_out.TexCoords = texture_coord;
    vs_out.FragPos = vec3(model * vec4(obj_pos, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));
    vs_out.Normal = normalMatrice * obj_normals;
    
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}  