#version 150
// ^ Change this to version 130 if you have compatibility issues

in vec4 fs_Col;

out vec4 out_Col;

void main()
{
    out_Col = fs_Col;
}
