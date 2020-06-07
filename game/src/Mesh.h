#pragma once
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Texture.h"
#include"Shader.h"
#include"vendor/glm/glm/glm.hpp"
#include"vendor/glm/glm/gtc/matrix_transform.hpp"
#include<memory>


struct Vertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
};

class Mesh
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<Shader> m_shader;
    Mesh(const std::string mesh_path, const std::string& shader_path);
    ~Mesh();
    void Bind() const;
    void UnBind() const;
};