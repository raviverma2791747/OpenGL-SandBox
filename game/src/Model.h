#pragma once
#include<assimp/mesh.h>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/Importer.hpp>
#include<string>
#include"Mesh.h"


class Model
{
private:
	std::string m_path;
	std::vector<Mesh> m_meshes;
public:
	Model(const std::string& path);
	~Model();
	void LoadModel();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
};
