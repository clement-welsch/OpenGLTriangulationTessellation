#shader vertex
#version 460 core
layout(location = 0) in vec4 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_mvp;
out vec2 uvs;

void main()
{
   gl_Position = position * u_mvp;
   uvs = texCoords;
};

#shader fragment
#version 460 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
in vec2 uvs;

void main()
{
   color = u_color;
   //color = vec4(uvs + 1.0, 0.000, 1.0)/2.0;
};