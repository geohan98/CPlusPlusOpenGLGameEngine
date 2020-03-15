#pragma once
#include <string>
#include <vector>
#include "Headers/renderer/mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace Engine
{
	class Model
	{
	private:
		std::vector<Mesh> m_meshes;
		std::string m_filepath;
		void LoadModel(const std::string& _filepath);
		void processNode(aiNode* _node, const aiScene* _scene);
		Mesh processMesh(aiMesh* _mesh, const aiScene* _scene);
	public:
		Model() {};
		Model(const std::string& _filePath);
		~Model();
		std::vector<std::shared_ptr<Renderer::Material>> getMaterials();
		int getNumMaterials() { return m_meshes.size(); }
	};
}