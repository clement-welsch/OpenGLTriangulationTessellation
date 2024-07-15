#version 460 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoords;


uniform mat4 u_mvp;
out vec2 uvs;

void main()
{
	gl_Position = pos * u_mvp;
	//gl_Position = pos;
	uvs = texCoords;
}