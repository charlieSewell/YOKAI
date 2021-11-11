//
// Created by charl on 1/03/2021.
//
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
/**
 * @struct Vertex
 * @brief Struct that holds vertex data
 */
struct Vertex
{
    ///position of vertex
    glm::vec3 position = {};
    ///normal of vertex
    glm::vec3 normal = {};
    ///texture coordinates of vertex
    glm::vec2 textureCoords = {};
    ///tangent of vertex
    glm::vec3 tangent = {};
    ///biTangent of vertex
    glm::vec3 biTangent = {};
    ///bone IDs
    glm::ivec4 boneIDs = {};
    ///bone weights
    glm::vec4 boneWeights = {};
};
/**
 * @class Texture
 * @brief Interface of a api specific texture
 */
class Texture
{
  public:
    /**
     * @brief Default destructor for texture
     */
    virtual ~Texture() = default;
    /**
     * @brief Binds a texture to a specific slot
     * @param size_t - slot
     */
    virtual void Bind(size_t slot) = 0;
    /**
     * @brief Unbinds a texture
     */
    virtual void UnBind(size_t slot) =0;
    /**
     * @brief Returns texture ID
     * @return int
     */
    virtual int GetID()=0;
    /**
     * @brief Creates a Texture in the currently selected RenderAPI
     * @param fileName
     * @return shared_ptr<Texture>
     */
    static std::shared_ptr<Texture> Create(const std::string& fileName);
};
/**
 * @struct ModelTexture
 * @brief struct that holds a texture as well as type and path
 */
struct ModelTexture 
{
    ///Texture for model
    std::shared_ptr<Texture> texture = nullptr;
    ///Type of texture
    std::string type = {};
    ///Path of texture
    std::string path = {};
};
/**
 * @class VertexBuffer
 * @brief Interface of a api specific vertex buffer
 */
class VertexBuffer
{
  public:
    /**
     *@brief Destructor of a Vertex Buffer
     */
    virtual ~VertexBuffer() = default;
    /**
     * @brief Binds a Vertex Buffer
     */
    virtual void Bind() = 0;
    /**
     * @brief Unbinds a Vertex Buffer
     */
    [[maybe_unused]] virtual void UnBind() =0;
    /**
     * @brief Creates a Vertex buffer in the currently selected RenderAPI
     * @param vector<Vertex> - vertices
     * @return shared_ptr<VertexBuffer>
     */
    static std::shared_ptr<VertexBuffer> Create(std::vector<Vertex> &vertices);
};
/**
 * @class IndexBuffer
 * @brief Interface of a api specific index buffer
 */
class IndexBuffer
{
  public:
    /**
     *@brief Destructor of an Index Buffer
     */
    virtual ~IndexBuffer() = default;
    /**
     * @brief Binds a Index Buffer
     */
    virtual void Bind() = 0;
    /**
     * @brief Unbinds a Index Buffer
     */
    virtual void UnBind() =0;
    /**
     * @brief Creates a Index Buffer in the currently selected RenderAPI
     * @param vector<unsigned int> - indices
     * @return shared_ptr<VertexBuffer>
     */
    static std::shared_ptr<IndexBuffer> Create(std::vector<unsigned int> &indices);
};
/**
 * @class VertexArrayBuffer
 * @brief Interface of a api specific vertex array buffer
 */
class VertexArrayBuffer
{
  public:
    virtual ~VertexArrayBuffer() =default;
    /**
     * @brief Binds a Vertex Array Buffer
     */
    virtual void Bind() = 0;
    /**
     * @brief Unbinds a Vertex Array Buffer
     */
    virtual void UnBind() =0;
    /**
     * @brief Creates a Vertex Array Buffer in the currently selected RenderAPI
     * @param vector<Vertex> - vertices
     * @param vector<unsigned int> - indices
     * @return shared_ptr<VertexArrayBuffer>
     */
    static std::shared_ptr<VertexArrayBuffer> Create(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
/**
 * @struct PointLight
 * @brief Stores point light info for GPU
 */
struct PointLight
{
  ///Color of light
	glm::vec4 color = {};
  ///Position of light
	glm::vec4 position = {};
  ///Padding and radius of light
	glm::vec4 paddingAndRadius = {};
};