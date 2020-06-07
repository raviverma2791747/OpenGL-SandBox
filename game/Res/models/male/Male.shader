#shader vertex
#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 n;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = proj * view * model * vec4(vp, 1.0);
}

#shader fragment
#version 330 core
out vec4 color;

uniform vec4 u_color;

void main()
{
	color = u_color;
}