#version 460 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
in vec2 uvs;

uniform sampler2D screen;

void main()
{
	color = u_color;
	//color = vec4(1.0,0.0,0.0,1.0);
}