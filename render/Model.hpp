#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture2D.hpp"

GLuint TextureFromFile(const GLchar* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    Model(const GLchar* path);
    Model(const Model&) = delete;

    Model& operator = (const Model&) = delete;

    GLvoid Draw(Shader& shader);
private:

    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    GLvoid loadModel(const std::string path);
    GLvoid processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
        aiTextureType type, const std::string typeName);
};

#endif