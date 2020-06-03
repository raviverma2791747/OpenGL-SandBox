#include"Mesh.h"
#include"VertexBufferLayout.h"

Mesh::Mesh(const std::vector<Vertex>& vertices,
	const std::vector<GLint>& indices,
	const std::vector<Texture2D>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	vao = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(&vertices, vertices.size() * (sizeof(glm::vec2) * (2 * sizeof(glm::vec3))));
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	vao->AddBuffer(*vb, vbl);
	ib = std::make_unique<IndexBuffer>(&indices,indices.size() * sizeof(GLuint));
	vao->Bind();
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	//for (;i<textures.size();i++)
	{

	}
}