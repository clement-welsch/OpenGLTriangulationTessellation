#shader vertex
#version 330 core

layout(location = 0) out vec4 position;

void main()
{
	gl_Position = position;
};