#version 460 core

// Quads
layout (vertices = 4) out;

in vec2 uvs[];
out vec2 uvsCoord[];

void main()
{
    float outer = 2.0;
    float inner = 1.0;
    gl_TessLevelOuter[0] = outer; // left for quads
    gl_TessLevelOuter[1] = outer; // bot for quads
    gl_TessLevelOuter[2] = outer; // right for quads
    gl_TessLevelOuter[3] = outer; // top for quads
        
    gl_TessLevelInner[0] = inner; // top bot for quads
    gl_TessLevelInner[1] = inner; // left right for quads

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];
}