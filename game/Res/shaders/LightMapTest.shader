#shader vertex
#version 330 core
layout(location = 0) in vec4 cb;
layout(location = 1) in vec3 nb;
layout(location = 2) in vec2 tc;

out vec3 normal;
out vec3 fragpos;
out vec2 texcoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * cb;
	fragpos = vec3(model * cb);
	normal = mat3(transpose(inverse(model))) * nb;
	texcoord = tc;
}

#shader fragment
#version 330 core
out vec4 color;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragpos;
in vec3 normal;
in vec2 texcoord;

uniform vec3 viewpos;
uniform Material material;
uniform Light light;

void main()
{
	//ambient
	vec3 ambient = light.ambient * texture(material.diffuse, texcoord).rgb;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightdir = normalize(light.position - fragpos);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texcoord).rgb;

	//specular
	vec3 viewdir = normalize(viewpos - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular,texcoord).rgb;
	vec3 result = ambient + diffuse + specular;

	color = vec4(result, 1.0);
}