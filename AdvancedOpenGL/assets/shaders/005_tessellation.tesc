#version 450 core

layout (vertices = 4) out;

uniform float inner;
uniform float outer;

void main(void)
{
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = inner;
        gl_TessLevelInner[1] = inner;
        gl_TessLevelOuter[0] = outer;
        gl_TessLevelOuter[1] = outer;
        gl_TessLevelOuter[2] = outer;
        gl_TessLevelOuter[3] = outer;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
