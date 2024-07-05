#version 460 core

// Quads
layout (vertices = 4) out;

in vec2 uvs[];
out vec2 uvsCoord[];

void main()
{
    gl_TessLevelOuter[0] = 1.0; // left for quads
    gl_TessLevelOuter[1] = 1.0; // bot for quads
    gl_TessLevelOuter[2] = 1.0; // right for quads
    gl_TessLevelOuter[3] = 1.0; // top for quads
        
    gl_TessLevelInner[0] = 1.0; // top bot for quads
    gl_TessLevelInner[1] = 1.0; // left right for quads

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];
}