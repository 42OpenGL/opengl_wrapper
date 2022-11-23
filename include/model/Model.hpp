//#pragma once

//#include "Mesh.hpp"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <glm/gtc/matrix_transform.hpp>


//class Model 
//{
//    private:
//        // model data
//        std::vector<Mesh> meshes;
//        std::string directory;

//        void loadModel(string path);
//        void processNode(aiNode *node, const aiScene *scene);
//        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
//                                             string typeName);
//    public:
//        Model(char *path)
//        {
//            loadModel(path);
//        }
        
//        void Draw(Shader &shader)
//        {
//            for(unsigned int i = 0; i < meshes.size(); i++)
//                meshes[i].Draw(shader);
//        }

//        void loadModel(string path)
//        {
//            Assimp::Importer import;
//            const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
            
//            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
//            {
//                cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
//                return;
//            }
//            directory = path.substr(0, path.find_last_of('/'));

//            processNode(scene->mRootNode, scene);
//        } 

//};