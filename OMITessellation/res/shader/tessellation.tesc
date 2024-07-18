#version 460 core

// Quads
layout (vertices = 4) out;

/*void main()
{
	float outer = 1.0;
	float inner = 1.0;
	gl_TessLevelOuter[0] = outer; // left for quads
	gl_TessLevelOuter[1] = outer; // bot for quads
	gl_TessLevelOuter[2] = outer; // right for quads
	gl_TessLevelOuter[3] = outer; // top for quads
		
	gl_TessLevelInner[0] = inner; // top bot for quads
	gl_TessLevelInner[1] = inner; // left right for quads

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}*/

void main(void)
{
	float outer = 1.0;
	float inner = 1.0;
	gl_TessLevelOuter[0] = 2.0;
	gl_TessLevelOuter[1] = 4.0;
	gl_TessLevelOuter[2] = 6.0;

	gl_TessLevelInner[0] = 8.0;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}