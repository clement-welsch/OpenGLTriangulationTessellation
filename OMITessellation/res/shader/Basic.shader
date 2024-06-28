#shader vertex
#version 410 core
layout(location = 0) in vec4 position;

uniform mat4 u_mvp;

void main()
{
   gl_Position = position * u_mvp;
};

#shader fragment
#version 410 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
   color = u_color;
};