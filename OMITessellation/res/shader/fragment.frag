#version 460 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
in vec2 uvs;

uniform sampler2D screen;

void main()
{
	//color = vec4(0.965, 0.318, 0.000, 1.0);
	//color = vec4(uvs + 1.0, 0.000, 1.0)/2.0 * u_color;
	color = u_color;
}