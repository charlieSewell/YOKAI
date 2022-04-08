//
// Created by Charlie Sewell on 1/04/2021.
//

#include "ModelLoader.hpp"
#include <algorithm>
#include <spdlog/spdlog.h>
#include <glm/gtx/string_cast.hpp>
static inline glm::mat4 to_glm(aiMatrix4x4t<float> &m){return glm::transpose(glm::make_mat4(&m.a1));}
static inline glm::vec3 vec3_cast(const aiVector3D &v) { return glm::vec3(v.x, v.y, v.z); }
static inline glm::quat quat_cast(const aiQuaternion &q) { return glm::quat(q.w, q.x, q.y, q.z); }

class AssimpLogger : public Assimp::LogStream
{
  public:
    // Write womethink using your own functionality
    void write(const char* message)
    {
      SPDLOG_INFO("{}",message);
    }
};

ModelLoader::ModelLoader()
{
    Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
    // Settings for aiProcess_SortByPType
    // only take triangles or higher (polygons are triangulated during import)
    m_importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
    // Settings for aiProcess_SplitLargeMeshes
    // Limit vertices to 65k (we use 16-bit indices)
    m_importer.SetPropertyInteger(AI_CONFIG_PP_SLM_VERTEX_LIMIT, std::numeric_limits<uint16_t>::max());

    const unsigned int severity = Assimp::Logger::Debugging|Assimp::Logger::Info|Assimp::Logger::Err|Assimp::Logger::Warn;
    Assimp::DefaultLogger::get()->attachStream(new AssimpLogger,severity);
}

ModelLoader::~ModelLoader()
{
    Assimp::DefaultLogger::kill();
}

Model ModelLoader::LoadModel(const std::string& filename)
{
    m_numBones = 0;
    std::vector<Mesh> meshes;
    std::vector<Bone> bones;
    std::vector<SkeletalAnimation> animations;
    std::map<std::string,unsigned int> boneMap;

    const aiScene *scene = m_importer.ReadFile(
        filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        SPDLOG_ERROR(m_importer.GetErrorString());
        return(Model(meshes));
    }
    // retrieve the directory path of the filepath
    m_directory = filename.substr(0, filename.find_last_of('/'));
    glm::mat4 globalInverseTransform = glm::inverse(to_glm(scene->mRootNode->mTransformation));
    // process ASSIMP's root node recursively
    ProcessNode(animations,meshes,bones,boneMap,scene->mRootNode, scene,to_glm(scene->mRootNode->mTransformation));
    
    for(auto& mesh: meshes)
    {
        mesh.SetupMesh();
    }
    //loadAnimNodes(rootAnimNode,scene->mRootNode);
    return Model(meshes,bones,boneMap,m_rootAnimNode,animations,globalInverseTransform);
}

void ModelLoader::ProcessNode(std::vector<SkeletalAnimation> &animations, std::vector<Mesh> &meshes, std::vector<Bone> &bones,
                              std::map<std::string, unsigned int> &boneMap, aiNode *node,
                              const aiScene *scene, glm::mat4 transform)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene, transform * to_glm(node->mTransformation)));
        if(scene->HasAnimations())
        {
            LoadBones(meshes, bones, boneMap, i, mesh);
            LoadAnimations(animations, scene);
            LoadAnimNodes(scene->mRootNode,mesh);
        }
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(animations,meshes,bones,boneMap,node->mChildren[i], scene, transform * to_glm(node->mTransformation));
    }
}

Mesh ModelLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene,glm::mat4 transform)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec4 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) 
        {
            // does the mesh contain texture coordinates?
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.textureCoords = vec;
        }
        else
        {
            vertex.textureCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(static_cast<uint16_t>(face.mIndices[j]));
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    Material newMaterial = LoadMaterial(material);
    // return a mesh object created from the extracted mesh data
    Mesh outMesh = Mesh(vertices, indices, transform, newMaterial);
    m_tangentCalculator.calc(&outMesh);
    return outMesh;
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<ModelTexture> ModelLoader::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
    std::vector<ModelTexture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(auto& j : m_textures_loaded)
        {
            if(std::strcmp(j.path.data(), str.C_Str()) == 0)
            {
                textures.push_back(j);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            ModelTexture texture;
            std::string fileName = m_directory +"/" + str.C_Str();
            texture.texture = m_textureManager.LoadTexture(fileName);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}
void ModelLoader::LoadAnimations(std::vector<SkeletalAnimation> &animations, const aiScene *scene){
    for(unsigned int i=0; i < scene->mNumAnimations;++i)
    {
        //Stores Each frame against the bone/node name
        std::map<std::string,Frame> animationMap;
        for(unsigned int j =0; j < scene->mAnimations[i]->mNumChannels; ++j)
        {
            //SkeletalAnimation for a singular bone
            Frame keyFrame = {};
            std::string name = scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str();
            keyFrame.numPositions = scene->mAnimations[i]->mChannels[j]->mNumPositionKeys;
            keyFrame.numRotations = scene->mAnimations[i]->mChannels[j]->mNumRotationKeys;
            for(unsigned int k=0; k < keyFrame.numPositions; ++k)
            {
                //Pushing back the Position at a certain time in the animation
                keyFrame.position.emplace_back(scene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime, vec3_cast(scene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mValue));
            }
            for(unsigned int k=0; k < keyFrame.numRotations; ++k)
            {
                //Pushing back the Rotation at a certain time in the animation
                keyFrame.rotation.emplace_back(scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mTime, quat_cast(scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mValue));
            }
            //Place it in a map with the name so animation can be called
            animationMap.emplace(name, keyFrame);
        }
        SkeletalAnimation anim = SkeletalAnimation(scene->mAnimations[i]->mName.C_Str(), animationMap, static_cast<float>(scene->mAnimations[i]->mDuration), static_cast<float>(scene->mAnimations[i]->mTicksPerSecond));
        animations.push_back(anim);
    }

}

aiNode* ModelLoader::FindRootNode(aiNode* node, aiMesh* mesh)
{
    std::vector<aiString> boneNames;
    boneNames.reserve(mesh->mNumBones);
    for(unsigned int i=0; i < mesh->mNumBones; ++i)
    {
        boneNames.push_back(mesh->mBones[i]->mName);
    }
    for(auto& boneName : boneNames)
    {
        aiNode* parent = node->FindNode(boneName)->mParent;
        if(!std::count(boneNames.begin(),boneNames.end(),parent->mName))
        {
            return parent;
        }
    }
    return nullptr;
}
Node ModelLoader::LoadNodeHeirachy(aiNode *rootNode)
{
    Node node;
    node.name = rootNode->mName.data;
    node.transform = to_glm(rootNode->mTransformation);
    node.childrenCount = rootNode->mNumChildren;

    for (unsigned int i = 0; i < node.childrenCount; ++i)
    {
        node.children.push_back(LoadNodeHeirachy(rootNode->mChildren[i]));
    }
    return node;
}

void ModelLoader::LoadAnimNodes(aiNode* node,aiMesh* mesh)
{
    auto rootNode = FindRootNode(node,mesh);
    if(rootNode == nullptr)
    {
        return;
    }
    m_rootAnimNode = LoadNodeHeirachy(rootNode);
}
void ModelLoader::LoadBones(std::vector<Mesh> &meshes, std::vector<Bone> &bones,std::map<std::string,unsigned int> &boneMap, unsigned int meshIndex, const aiMesh *mesh)
{
    for (size_t i = 0 ; i < mesh->mNumBones; ++i) {
        unsigned int boneIndex;
        std::string boneName(mesh->mBones[i]->mName.data);

        if (boneMap.find(boneName) == boneMap.end())
        {
            boneIndex = m_numBones;
            ++m_numBones;
            Bone bi;
            bones.push_back(bi);
        }
        else
        {
            boneIndex = boneMap[boneName];
        }

        boneMap[boneName] = boneIndex;
        bones[boneIndex].offset = to_glm(mesh->mBones[i]->mOffsetMatrix);

        for (size_t j = 0 ; j < mesh->mBones[i]->mNumWeights; ++j)
        {
            unsigned VertexID = mesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = mesh->mBones[i]->mWeights[j].mWeight;
            meshes.at(meshIndex).addBoneData(VertexID, static_cast<uint16_t>(boneIndex), Weight);
        }
    }
}

Material ModelLoader::LoadMaterial(const aiMaterial* material)
{
    Material out;

    out.baseColorTexture = m_textureManager.LoadTexture("content/textures/dummy/dummy_white.dds");
    out.metallicRoughnessTexture = m_textureManager.LoadTexture("content/textures/dummy/dummy_metallicRoughness.dds");
    out.normalTexture = m_textureManager.LoadTexture("content/textures/dummy/dummy_normal_map.dds");
    out.emissiveTexture = m_textureManager.LoadTexture("content/textures/dummy/dummy_white.dds");
    out.occlusionTexture = m_textureManager.LoadTexture("content/textures/dummy/dummy_white.dds");
    // there is a purpose of mask and blend but we dont need it
    aiString alphaMode;
    material->Get(AI_MATKEY_GLTF_ALPHAMODE, alphaMode);
    aiString alphaModeOpaque;
    alphaModeOpaque.Set("OPAQUE");
    out.blend = alphaMode != alphaModeOpaque;
    
    material->Get(AI_MATKEY_TWOSIDED, out.doubleSided);

    // texture files

    aiString fileBaseColor, fileMetallicRoughness, fileNormals, fileOcclusion, fileEmissive;
    material->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &fileBaseColor);
    material->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE, &fileMetallicRoughness);
    material->GetTexture(aiTextureType_NORMALS, 0, &fileNormals);
    material->GetTexture(aiTextureType_LIGHTMAP, 0, &fileOcclusion);
    material->GetTexture(aiTextureType_EMISSIVE, 0, &fileEmissive);

    // Base color

    if(fileBaseColor.length > 0)
    {
        aiString pathBaseColor;
        pathBaseColor.Set(m_directory + "/");
        pathBaseColor.Append(fileBaseColor.C_Str());
        SPDLOG_INFO("Loaded Base Color: {}",pathBaseColor.C_Str());
        out.baseColorTexture = m_textureManager.LoadTexture(pathBaseColor.C_Str());
    }
    
    aiColor4D baseColorFactor;
    if(AI_SUCCESS == material->Get(AI_MATKEY_BASE_COLOR, baseColorFactor))
        out.baseColorFactor = { baseColorFactor.r, baseColorFactor.g, baseColorFactor.b, baseColorFactor.a };

    // metallic/roughness

    if(fileMetallicRoughness.length > 0)
    {
        aiString pathMetallicRoughness;
        pathMetallicRoughness.Set(m_directory + "/");
        pathMetallicRoughness.Append(fileMetallicRoughness.C_Str());
        SPDLOG_INFO("Loaded Metalic/Roughness Texture: {}", pathMetallicRoughness.C_Str());
        out.metallicRoughnessTexture = m_textureManager.LoadTexture(pathMetallicRoughness.C_Str());
    }

    ai_real metallicFactor;
    if(AI_SUCCESS == material->Get(AI_MATKEY_METALLIC_FACTOR, metallicFactor))
        out.metallicFactor = metallicFactor;
    ai_real roughnessFactor;
    if(AI_SUCCESS == material->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughnessFactor))
        out.roughnessFactor = roughnessFactor;

    // normal map

    if(fileNormals.length > 0)
    {
        aiString pathNormals;
        pathNormals.Set(m_directory + "/");
        pathNormals.Append(fileNormals.C_Str());
        SPDLOG_INFO("Normal Map Texture: {}", pathNormals.C_Str());
        out.normalTexture = m_textureManager.LoadTexture(pathNormals.C_Str());
    }

    ai_real normalScale;
    if(AI_SUCCESS == material->Get(AI_MATKEY_GLTF_TEXTURE_SCALE(aiTextureType_NORMALS, 0), normalScale))
        out.normalScale = normalScale;

    // occlusion texture

    if(fileOcclusion == fileMetallicRoughness)
    {
        // some GLTF files combine metallic/roughness and occlusion values into one texture
        // don't load it twice
        out.occlusionTexture = out.metallicRoughnessTexture;
        SPDLOG_INFO("Loaded Occlusion Texture: {}", fileMetallicRoughness.C_Str());
    }
    else if(fileOcclusion.length > 0)
    {
        aiString pathOcclusion;
        pathOcclusion.Set(m_directory + "/");
        pathOcclusion.Append(fileOcclusion.C_Str());
        SPDLOG_INFO("Loaded Occlusion Texture: {}", fileMetallicRoughness.C_Str());
        out.occlusionTexture = m_textureManager.LoadTexture(pathOcclusion.C_Str());
    }

    ai_real occlusionStrength;
    if(AI_SUCCESS == material->Get(AI_MATKEY_GLTF_ALPHACUTOFF, occlusionStrength))
        out.occlusionStrength = glm::clamp(occlusionStrength, 0.0f, 1.0f);

    // emissive texture

    if(fileEmissive.length > 0)
    {
        aiString pathEmissive;
        pathEmissive.Set(m_directory + "/");
        pathEmissive.Append(fileEmissive.C_Str());
        SPDLOG_INFO("Loaded Emmisive Texture: {}", pathEmissive.C_Str());
        out.emissiveTexture = m_textureManager.LoadTexture(pathEmissive.C_Str());
    }

// assimp doesn't define this
#ifndef AI_MATKEY_GLTF_EMISSIVE_FACTOR
#define AI_MATKEY_GLTF_EMISSIVE_FACTOR AI_MATKEY_COLOR_EMISSIVE
#endif

    aiColor3D emissiveFactor;
    if(AI_SUCCESS == material->Get(AI_MATKEY_GLTF_EMISSIVE_FACTOR, emissiveFactor))
        out.emissiveFactor = { emissiveFactor.r, emissiveFactor.g, emissiveFactor.b , 1.0f};

    return out;
}