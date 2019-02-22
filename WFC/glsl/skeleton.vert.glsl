#version 150

uniform mat4 u_Model;
uniform mat4 u_ViewProj;
uniform mat4 u_ModelInvTr;  // The inverse transpose of the model matrix.
                            // This allows us to transform the object's normals properly
                            // if the object has been non-uniformly scaled.
in vec4 vs_Pos;
in vec4 vs_Col;
in vec4 vs_Nor;

in uvec2 vs_InfluencerIDs;
in vec2 vs_Influences;

uniform mat4 u_BindMatrices[100];
uniform mat4 u_JointTransformations[100];

out vec4 fs_Col;
out vec4 fs_Nor;
out vec4 fs_LightVec;

const vec4 lightPos = vec4(5, 5, 3, 1);

void main()
{
    fs_Col = vs_Col;                         // Pass the vertex colors to the fragment shader for interpolation

    mat3 invTranspose = mat3(u_ModelInvTr);
    fs_Nor = vec4(invTranspose * vec3(vs_Nor), 0);          // Pass the vertex normals to the fragment shader for interpolation.
                                                            // Transform the geometry's normals by the inverse transpose of the
                                                            // model matrix. This is necessary to ensure the normals remain
                                                            // perpendicular to the surface after the surface is transformed by
                                                            // the model matrix.


    vec4 modelposition = u_Model * vs_Pos;   // Temporarily store the transformed vertex positions for use below

    fs_LightVec = lightPos - modelposition;  // Compute the direction in which the light source lies

    vec4 intermediatePos = u_ViewProj * modelposition;

    vec4 pos1 = u_JointTransformations[vs_InfluencerIDs[0]] * u_BindMatrices[vs_InfluencerIDs[0]] * intermediatePos;
    vec4 pos2 = u_JointTransformations[vs_InfluencerIDs[1]] * u_BindMatrices[vs_InfluencerIDs[1]] * intermediatePos;

    // interpolate between two positions
    gl_Position = vs_Influences[0] * pos1 + vs_Influences[1] * pos2;
}
