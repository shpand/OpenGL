#pragma once

#include "../Shader.h";
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

namespace  open_gl_engine {

	class Model
	{
	public:
		/*  Functions   */
		Model(char* path)
		{
			loadModel(path);
		}
		void Draw(Shader shader);
	private:
		/*  Model Data  */
		vector<Texture> textures_loaded;
		vector<Mesh> meshes;
		string directory;
		/*  Functions   */
		void loadModel(string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			string typeName);
	};
}
