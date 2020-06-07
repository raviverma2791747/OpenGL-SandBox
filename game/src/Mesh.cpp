#include"Mesh.h"
#include"VertexBufferLayout.h"
#include"assimp/postprocess.h"
#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include<iostream>


Mesh::Mesh(const std::string mesh_path, const std::string& shader_path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(mesh_path.c_str(), aiProcess_Triangulate | aiProcess_GenNormals);
    if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode))
    {
        std::cerr << "Error loading "<<mesh_path<<" "<< std::string(importer.GetErrorString()) << std::endl;
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
            Vertex tempVertex;

            //Set the positions
            tempVertex.Position.x = mesh->mVertices[j].x;
            tempVertex.Position.y = mesh->mVertices[j].y;
            tempVertex.Position.z = mesh->mVertices[j].z;

            //Set the normals
            tempVertex.Normal.x = mesh->mNormals[j].x;
            tempVertex.Normal.y = mesh->mNormals[j].y;
            tempVertex.Normal.z = mesh->mNormals[j].z;

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
    m_vb = std::make_unique<VertexBuffer>(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(3);
    m_vao->AddBuffer(*m_vb, vbl);
    m_ib = std::make_unique<IndexBuffer>(&m_indices[0], m_indices.size());
    m_shader = std::make_unique<Shader>(shader_path);
    m_shader->Bind();
}

Mesh::~Mesh()
{
	
}

void Mesh::Bind() const
{
    m_vao->Bind();
    m_vb->Bind();
    m_ib->Bind();
    m_shader->Bind();
}

void Mesh::UnBind() const
{
    m_vao->Unbind();
    m_vb->UnBind();
    m_ib->UnBind();
    m_shader->Unbind();
}

 