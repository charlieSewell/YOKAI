#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
/**
 * @class ReactMath
 * @brief Helper class for glm to rp3d
 */
namespace ReactMath {
    /**
     * @brief Converts glm quat to rp3d
     * @param glm::quat - quat
     * @return rp3d::Quaternion - quat
     */
    reactphysics3d::Quaternion glmQuatToRP3d(glm::quat &quat);
    /**
     * @brief Converts rp3d quat to glm
     * @param rp3d::Quaternion - quat
     * @return glm::quat - quat
     */
    glm::quat rp3dQuatToGlm(reactphysics3d::Quaternion &quat);
    /**
     * @brief Converts glm vec3 to rp3d
     * @param glm::vec3 - vec3
     * @return rp3d::Vector3 - vec3
     */
    reactphysics3d::Vector3 glmVecToRP3d(glm::vec3 &vec);
    /**
     * @brief glm vec3 to rp3d
     * @param glm::vec3 - vec3
     * @return rp3d::Vector3 - vec3
     */
    reactphysics3d::Vector3 glmVecToRP3d(glm::dvec3 &vec);
    /**
     * @brief Converts rp3d Vector3 to glm
     * @param rp3d::Vector3 - vec3
     * @return glm::vec3 - vec3
     */
    glm::vec3 rp3dVecToGlm(reactphysics3d::Vector3 &vec);
    /**
     * @brief Converts rp3d Vector3 to glm
     * @param rp3d::Vector3 - vec3
     * @return glm::dvec3 - vec3
     */
    glm::dvec3 rp3dVecToGlmD(reactphysics3d::Vector3 &vec);
    /**
     * @brief Converts rp3d Transform to glm
     * @param rp3d::Transform - transform
     * @return glm::mat4 - transform
     */
    glm::mat4 rp3dMat4ToGlm(reactphysics3d::Transform &transform);
}