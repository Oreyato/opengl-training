#version 450 core

layout (vertices = 4) out;  // vertices = number of control point / patch

uniform float innerWidth;
uniform float innerLength;
uniform float outerWidth;
uniform float outerLength;

void main(void)
{
    // tesselation 0 controls the level of tesselation for the entire patch
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = innerWidth;
        gl_TessLevelInner[1] = innerLength;
        gl_TessLevelOuter[0] = outerLength;
        gl_TessLevelOuter[1] = outerWidth;
        gl_TessLevelOuter[2] = outerLength;
        gl_TessLevelOuter[3] = outerWidth;
    }
    // Now copy its input into its output with gl_out and gl_in
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}