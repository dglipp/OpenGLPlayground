#include <INTERNAL/Loader.h>

#include <iostream>
#include <vector>
#include <regex>

#include <INTERNAL/Geometry.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <VENDOR/GLM/glm.hpp>

namespace load
{
    geo::Mesh ObjLoader::loadMesh()
    {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(m_file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
        {
            std::cout << "[ASSIMP ERROR]: " << importer.GetErrorString() << '\n';
            return geo::Mesh();
        }

        aiNode *node = scene->mRootNode->mChildren[0];
        aiMesh *mesh = scene->mMeshes[0];

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<unsigned int> indices;

        for (int i = 0; i < mesh->mNumVertices; ++i)
        {
            vertices.push_back(glm::vec3(
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z));

            if (mesh->mTextureCoords[0])
            {
                texCoords.push_back(glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y));
            }

            normals.push_back(glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z));
        }

        for (int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }
        
        return geo::Mesh(vertices, normals, texCoords, indices);
    }
}