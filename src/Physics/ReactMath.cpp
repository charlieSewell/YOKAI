//
// Created by charl on 19/05/2021.
//

#include "ReactMath.hpp"
reactphysics3d::Quaternion ReactMath::glmQuatToRP3d(glm::quat& quat) {
    rp3d::Quaternion newQuat = {};
    newQuat.x = quat.x;
    newQuat.y = quat.y;
    newQuat.z = quat.z;
    newQuat.w = quat.w;
    return newQuat;
}
glm::quat ReactMath::rp3dQuatToGlm(reactphysics3d::Quaternion& quat) {
    glm::quat newQuat = {};
    newQuat.x = quat.x;
    newQuat.y = quat.y;
    newQuat.z = quat.z;
    newQuat.w = quat.w;
    return newQuat;
}
reactphysics3d::Vector3 ReactMath::glmVecToRP3d(glm::vec3 &vec) {
    rp3d::Vector3 newVec = {};
    newVec.x = vec.x;
    newVec.y = vec.y;
    newVec.z = vec.z;
    return newVec;
}
/*
glm::vec3 ReactMath::rp3dVecToGlm(reactphysics3d::Vector3 &vec){
    glm::vec3 newVec = {};
    newVec.x = vec.x;
    newVec.y = vec.y;
    newVec.z = vec.z;
    return newVec;
}
*/
glm::vec3 ReactMath::rp3dVecToGlm(reactphysics3d::Vector3 vec) {
    glm::vec3 newVec = {};
    newVec.x         = vec.x;
    newVec.y         = vec.y;
    newVec.z         = vec.z;
    return newVec;
}