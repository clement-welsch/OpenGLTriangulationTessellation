#version 460 core

uniform float u_inner;
uniform float u_outer;

layout (vertices = 3) out;

void main(void)
{
	gl_TessLevelOuter[0] = u_outer;
	gl_TessLevelOuter[1] = u_outer;
	gl_TessLevelOuter[2] = u_outer;

	gl_TessLevelInner[0] = u_inner;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}