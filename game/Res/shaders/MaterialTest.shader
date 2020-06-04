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

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 normal;
in vec3 fragpos;
uniform vec3 viewpos;
uniform Material material;
uniform Light light;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightdir = normalize(light.position - fragpos);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
	vec3 viewdir = normalize(viewpos - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
}