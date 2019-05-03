#version 150
// ^ Change this to version 130 if you have compatibility issues

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;
in vec2 fs_UV;

out vec4 out_Col;

void main()
{
    vec4 diffuseColor = texture(u_Texture, fs_UV);

    // Calculate the diffuse term for Lambert shading
    float diffuseTerm = dot(normalize(fs_Nor), normalize(fs_LightVec));

    // Avoid negative lighting values
    diffuseTerm = clamp(diffuseTerm, 0, 1);

    float ambientTerm = 0.2;

    float lightIntensity = diffuseTerm + ambientTerm;   //Add a small float value to the color multiplier
                                                            //to simulate ambient lighting. This ensures that faces that are not
                                                            //lit by our point light are not completely black.



    // add some distance fog
    vec3 fogColor = vec3(0.53, 0.81, 0.92);

    // get "depth" from eye to fragment

    float depth = (gl_FragCoord.z / gl_FragCoord.w) / 150.f;
    depth = clamp(depth, 0, 1);

   // depth = 0;

    // Compute final shaded color
    // linearly interpolate with fog color based on depth
    out_Col = vec4(mix(diffuseColor.rgb * lightIntensity, fogColor, depth), diffuseColor.a);


    // Compute final shaded color
    //out_Col = vec4(diffuseColor.rgb * lightIntensity, diffuseColor.a);
}

