#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <stbi/stb_image.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
private:
	// model data
	std::vector<Mesh> _meshes;
	std::string _directory;
    std::vector<MeshTexture> _textures_loaded;
    bool _gamma_correction;

	void loadModel(const std::string & path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string & typeName);
    
public:
	Model(const std::string & path, bool gamma = false);
	
	void Draw(const ShaderProgram & shader);
};

Model::Model(const std::string & filepath, bool gamma)
{
	loadModel(filepath);
	_gamma_correction = gamma;
}

void Model::Draw(const ShaderProgram & shader)
{
	for(unsigned int i = 0; i < _meshes.size(); i++)
			_meshes[i].Draw(shader);
}

void Model::loadModel(const std::string & path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
} 

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// process all the node's meshes (if any)
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
		_meshes.push_back(processMesh(mesh, scene));			
	}
	// then do the same for each of its children
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture> textures;

    // process vertex
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex vertex;
		glm::vec3 vector; 
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z; 
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x; 
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
		vertices.push_back(vertex);
	}
	// process indices
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	} 
	
	// process material
	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<MeshTexture> diffuseMaps = loadMaterialTextures(material,
											aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<MeshTexture> specularMaps = loadMaterialTextures(material, 
											aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}


	return Mesh(vertices, indices, textures);
}


std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string & typeName)
{
	std::vector<MeshTexture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for(unsigned int j = 0; j < _textures_loaded.size(); j++)
		{
			if(std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(_textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		// if texture hasn't been loaded already, load it
		if(!skip)
		{
			MeshTexture texture;
			texture.id = TextureFromFile(str.C_Str(), this->_directory);
			texture.type = typeName;
		}
	}
	return textures;
}  

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 3);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}