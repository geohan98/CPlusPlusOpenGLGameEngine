#pragma once

#pragma message("Non-Risky")
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../stb_image/stb_image.h"


#pragma message("Assimp")
#include "../assimp/include/assimp/mesh.h"
#include "../assimp/include/assimp/scene.h"
#include "../assimp/include/assimp/material.h"
#include "../assimp/include/assimp/postprocess.h"
#include "../assimp/include/assimp/Importer.hpp"

#pragma message("OpenGL Infrastructure Headers")
#include "../enginecode/Headers/OpenGL/OpenGL_shader.h"
#include "../enginecode/Headers/OpenGL/OpenGL_vertexArray.h"

#pragma message("Includes complete.")

using namespace std;

namespace Engine 
{

	namespace Renderer 
	{
        unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

		struct Vertex {
			// position
			glm::vec3 Position;
			// normal
			glm::vec3 Normal;
			// texCoords
			glm::vec2 TexCoords;
			// tangent
			glm::vec3 Tangent;
			// bitangent
			glm::vec3 Bitangent;
		};


		class Mesh {
		public:
			struct Texture {
				unsigned int id;
				string type;
				string path;
			};

			/*  Mesh Data  */
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<Texture> textures;
			unsigned int VAO;

			/*  Functions  */
			// constructor
			Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Mesh::Texture> textures)
			{
				this->vertices = vertices;
				this->indices = indices;
				this->textures = textures;

				// now that we have all the required data, set the vertex buffers and its attribute pointers.
				setupMesh();
			}

			// render the mesh
			void Draw(const std::shared_ptr<Shader>& shader);

		private:
			/*  Render data  */
			unsigned int VBO, EBO;

			/*  Functions    */
			// initializes all the buffer objects/arrays
			void setupMesh();
		};	
		
		class OBJModel
		{
		public:
			/*  Model Data */
			vector<Mesh::Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
			vector<Mesh> meshes;
			string directory;
			bool gammaCorrection;

			/*  Functions   */
			// constructor, expects a filepath to a 3D model.
			OBJModel(string const &path, bool gamma = false) : gammaCorrection(gamma)
			{
				loadModel(path);
			}


		private:
			/*  Functions   */
			// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
			void loadModel(string const &path);

			// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
			void processNode(aiNode *node, const aiScene *scene);

			Mesh processMesh(aiMesh *mesh, const aiScene *scene);

			// checks all material textures of a given type and loads the textures if they're not loaded yet.
			// the required info is returned as a Texture struct.
			vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
		};

		
	};

}


		