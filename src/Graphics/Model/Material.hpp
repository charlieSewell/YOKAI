#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Renderer/DataTypes.hpp"

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#metallic-roughness-material
struct Material
{
    bool blend = false;
    bool doubleSided = false;

    std::shared_ptr<Texture> baseColorTexture;
    glm::vec4 baseColorFactor = { 1.0f, 1.0f, 1.0f, 1.0f };

    std::shared_ptr<Texture> metallicRoughnessTexture = nullptr; // blue = metallic, green = roughness
    float metallicFactor = 1.0f;
    float roughnessFactor = 1.0f;

    std::shared_ptr<Texture> normalTexture = nullptr;
    float normalScale = 1.0f;

    std::shared_ptr<Texture> occlusionTexture = nullptr;
    float occlusionStrength = 0.5f;

    std::shared_ptr<Texture> emissiveTexture = nullptr;
    glm::vec4 emissiveFactor = { 0.0f, 0.0f, 0.0f ,1.0f};
};