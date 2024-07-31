#version 460 core

// Quads
layout (vertices = 3) out;

void main(void)
{
	float outer = 1.0;
	float inner = 0.0;
	gl_TessLevelOuter[0] = outer;
	gl_TessLevelOuter[1] = outer;
	gl_TessLevelOuter[2] = outer;

	gl_TessLevelInner[0] = inner;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}