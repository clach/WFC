#version 150
// ^ Change this to version 130 if you have compatibility issues

// Refer to the lambert shader files for useful comments

in vec4 fs_Col;

out vec4 out_Col;

uniform vec4 u_Color; // The color with which to render this instance of geometry.


void main()
{
    // Copy the color; there is no shading.
    out_Col = u_Color;
}
