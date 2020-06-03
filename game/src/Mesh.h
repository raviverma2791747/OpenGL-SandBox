#pragma once
#include"Renderer.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"Texture.h"
#include"vendor/glm/glm/glm.hpp"
#include"vendor/glm/glm/gtc/matrix_transform.hpp"
#include"memory"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
private:
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vb;
    std::unique_ptr<IndexBuffer> ib;
    std::unique_ptr<Shader> shader;
    std::vector<Vertex> vertices;
    std::vector<GLint> indices;
    std::vector<Texture2D> textures;
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<GLint>& indices,
        const std::vector<Texture2D>& textures );
    ~Mesh();
    void Draw();
};