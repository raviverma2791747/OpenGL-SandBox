#shader vertex
#version 330 core
layout(location = 0) in vec4 cb;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * cb;
}

#shader fragment
#version 330 core
out vec4 color;
uniform vec4 cc;
void main()
{
	color = cc;
}