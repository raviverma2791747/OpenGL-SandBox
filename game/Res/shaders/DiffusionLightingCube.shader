#shader vertex
#version 330 core
layout(location = 0) in vec4 cb;
layout(location = 1) in vec3 nb;

out vec3 normal;
out vec3 fragpos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * cb;
	fragpos = vec3(model * cb);
	normal = mat3(transpose(inverse(model))) * nb;
}

#shader fragment
#version 330 core
out vec4 color;

in vec3 normal;
in vec3 fragpos;
uniform vec4 cc;
uniform vec3 lightcolor;
uniform vec3 lightpos;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightdir = normalize(lightpos - fragpos);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = diff * lightcolor;
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightcolor;
	vec3 result = ambient + diffuse;
	color = vec4(result, 1.0) * cc;
}