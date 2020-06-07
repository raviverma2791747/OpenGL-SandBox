#pragma once
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"Texture.h"
#include"Shader.h"
#include"vendor/glm/glm/glm.hpp"
#include"vendor/glm/glm/gtc/matrix_transform.hpp"
#include<memory>
#include"assimp/postprocess.h"
#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include<iostream>



struct Vertex2
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

struct Vertex3
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

struct Vertex5
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
    glm::vec3 Tangent;
    glm::vec3 BiTangent;
};

template<typename T>
class Mesh
{
private:
    std::vector<T> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<Shader> m_shader;
    Mesh(const std::string mesh_path, const std::string& shader_path)
    {
        std::string m_type = typeid(T).name();
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(mesh_path.c_str(), aiProcess_Triangulate | aiProcess_GenNormals);
        if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode))
        {
            std::cerr << "Error loading " << mesh_path << " " << std::string(importer.GetErrorString()) << std::endl;
            //Return fail
            return;
        }
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            //Get the mesh
            aiMesh* mesh = scene->mMeshes[i];

            //Iterate over the vertices of the mesh
            for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
            {
                //Create a vertex to store the mesh's vertices temporarily
                T tempVertex;
                if (m_type == "struct Vertex2")
                {
                    //Set the positions
                    tempVertex.Position.x = mesh->mVertices[j].x;
                    tempVertex.Position.y = mesh->mVertices[j].y;
                    tempVertex.Position.z = mesh->mVertices[j].z;

                    //Set the normals
                    tempVertex.Normal.x = mesh->mNormals[j].x;
                    tempVertex.Normal.y = mesh->mNormals[j].y;
                    tempVertex.Normal.z = mesh->mNormals[j].z;
                }
                //Add the vertex to the vertices vector
                m_vertices.push_back(tempVertex);
            }

            //Iterate over the faces of the mesh
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
            {
                //Get the face
                aiFace face = mesh->mFaces[j];
                //Add the indices of the face to the vector
                for (unsigned int k = 0; k < face.mNumIndices; ++k) { m_indices.push_back(face.mIndices[k]); }
            }
        }
        m_vao = std::make_unique<VertexArray>();
        m_vb = std::make_unique<VertexBuffer>(&m_vertices[0], m_vertices.size() * sizeof(T));
        VertexBufferLayout vbl;
        if ( m_type == "struct Vertex2")
        {
            vbl.Push<float>(3);
            vbl.Push<float>(3);
        }
        m_vao->AddBuffer(*m_vb, vbl);
        m_ib = std::make_unique<IndexBuffer>(&m_indices[0], m_indices.size());
        m_shader = std::make_unique<Shader>(shader_path);
        m_shader->Bind();
    }

    ~Mesh()
    {

    }

    void Bind() const
    {
        m_vao->Bind();
        m_vb->Bind();
        m_ib->Bind();
        m_shader->Bind();
    }

    void UnBind() const
    {
        m_vao->Unbind();
        m_vb->UnBind();
        m_ib->UnBind();
        m_shader->Unbind();
    }
};