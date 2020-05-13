#include "engine_pch.h"
#include "Headers/renderer/model.h"
#include "Headers/systems/log.h"

namespace Engine
{

	Model::Model(const std::string& _filePath)
	{
		LoadModel(_filePath);
		LOG_CORE_INFO("[MODEL][CONSTRUCTOR][NUMBER OF MESHES: {0}]", m_meshes.size());
	}
	Model::~Model()
	{
	}

	std::vector<std::shared_ptr<Renderer::Material>> Model::getMaterials()
	{
		std::vector<std::shared_ptr<Renderer::Material>> materials;

		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i].rebindTexture(); // makes sure we're using the correct texture before getting the material
			materials.push_back(m_meshes[i].getMaterial());

		}
		return materials;
	}

	void Model::LoadModel(const std::string& _filepath)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(_filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_CORE_ERROR("[MODEL][LOADMODEL][UNABLE TO LOAD MODEL: {0}]", _filepath);
			return;
		}
		m_filepath = _filepath;
		processNode(scene->mRootNode, scene);
		LOG_CORE_INFO("[MODEL][LOADMODEL][LOADED MODEL: {0}]", m_filepath);
	}

	void Model::processNode(aiNode* _node, const aiScene* _scene)
	{
		for (unsigned int i = 0; i < _node->mNumMeshes; i++)
		{
			aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, _scene));
			//LOG_CORE_INFO("[MODEL][PROCESSNODE][PUSHED BACK MESH]");
		}
		for (unsigned int i = 0; i < _node->mNumChildren; i++)
		{
			processNode(_node->mChildren[i], _scene);
		}
	}

	Mesh Model::processMesh(aiMesh* _mesh, const aiScene* _scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector3;
			//Positions
			vector3.x = _mesh->mVertices[i].x;
			vector3.y = _mesh->mVertices[i].y;
			vector3.z = _mesh->mVertices[i].z;
			vertex.position = vector3;
			//Normals
			vector3.x = _mesh->mNormals[i].x;
			vector3.y = _mesh->mNormals[i].y;
			vector3.z = _mesh->mNormals[i].z;
			vertex.normal = vector3;
			//Texture Coordinates
			if (_mesh->mTextureCoords[0])
			{
				glm::vec2 vector2;
				vector2.x = _mesh->mTextureCoords[0][i].x;
				vector2.y = _mesh->mTextureCoords[0][i].y;
				vertex.texCoords = vector2;
			}
			else
			{
				vertex.texCoords = glm::vec2(0.0f, 0.0f);
			}
			//Tangent
			vector3.x = _mesh->mTangents[i].x;
			vector3.y = _mesh->mTangents[i].y;
			vector3.z = _mesh->mTangents[i].z;
			vertex.tangent = vector3;
			//Bitangent
			vector3.x = _mesh->mBitangents[i].x;
			vector3.y = _mesh->mBitangents[i].y;
			vector3.z = _mesh->mBitangents[i].z;
			vertex.bitangent = vector3;
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
		{
			aiFace face = _mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		LOG_CORE_INFO("[MODEL][PROCESSMESH][NUMBER OF VERTICES: {0}]", vertices.size());
		LOG_CORE_INFO("[MODEL][PROCESSMESH][NUMBER OF INDICES: {0}]", indices.size());

		aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
		aiString filepath;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &filepath);
		if (filepath.length > 0)
		{
			std::string filename = m_filepath;
			int pos = filename.find_last_of("/");
			filename = filename.substr(0, pos);
			filename += "/" + std::string(filepath.C_Str());
			return Mesh(vertices, indices, filename);
		}
		else
		{
			return Mesh(vertices, indices, "");
		}




	}
}