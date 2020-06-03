#shader vertex
#version 330 core
layout(location = 0) in vec4 cb;
layout(location = 1) in vec2 texcoord;

out vec2 v_texcoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * cb;
	v_texcoord = texcoord;
}

#shader fragment
#version 330 core
out vec4 color;
in vec2 v_texcoord;
uniform sampler2D u_texture;

void main()
{
	vec4 texcolor = texture(u_texture, v_texcoord);
	color = texcolor;
}