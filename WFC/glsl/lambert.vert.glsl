#version 150
// ^ Change this to version 130 if you have compatibility issues

uniform mat4 u_Model;
uniform mat4 u_ModelInvTr;
uniform mat4 u_ViewProj;

in vec4 vs_Pos;
in vec4 vs_Nor;
in vec4 vs_Col;
in vec2 vs_UV;

in vec3 vs_Trans;
in vec3 vs_Rot;

out vec4 fs_Nor;
out vec4 fs_LightVec;
out vec4 fs_Col;
out vec2 fs_UV;

const vec4 lightPos = vec4(50, 50, 0, 1);

void main()
{
    fs_UV = vs_UV;

    fs_Col = vs_Col;

    mat3 invTranspose = mat3(u_ModelInvTr);
    fs_Nor = vec4(invTranspose * vec3(vs_Nor), 0);

    vec4 newPos = vec4(vec3(vs_Pos) + vs_Trans, 1.0);
    vec4 modelposition = u_Model * newPos;

    fs_LightVec = lightPos - modelposition;

    gl_Position = u_ViewProj * modelposition;
}
