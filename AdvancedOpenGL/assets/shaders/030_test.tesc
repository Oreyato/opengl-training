#version 450 core

layout (vertices = 3) out;  // vertices = number of control point / patch

uniform float inner;
uniform float outer;

void main(void)
{
    // tesselation 0 controls the level of tesselation for the entire patch
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = inner;
        gl_TessLevelOuter[0] = outer;
        gl_TessLevelOuter[1] = outer;
        gl_TessLevelOuter[2] = outer;
    }
    // Now copy its input into its output with gl_out and gl_in
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}