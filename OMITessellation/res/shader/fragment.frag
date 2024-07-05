#version 460 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
in vec2 uvs;

uniform sampler2D screen;

void main()
{
	//FragColor = vec4(0.965, 0.318, 0.000, 1.0);
	//FragColor = vec4(uvs + 1.0, 0.000, 1.0)/2.0;
	 color = u_color;
}