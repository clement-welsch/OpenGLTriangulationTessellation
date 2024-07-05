#version 460 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_mvp;
out vec2 uvs;

void main()
{
	//gl_Position = vec4(pos.xyz, 1.0);
	gl_Position = pos * u_mvp;
	uvs = texCoords;
}