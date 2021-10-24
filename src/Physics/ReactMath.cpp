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
reactphysics3d::Vector3 ReactMath::glmVecToRP3d(glm::dvec3 &vec) {
    rp3d::Vector3 newVec = {};
    newVec.x             = vec.x;
    newVec.y             = vec.y;
    newVec.z             = vec.z;
    return newVec;
}
///*
glm::vec3 ReactMath::rp3dVecToGlm(reactphysics3d::Vector3 &vec){
    glm::vec3 newVec = {};
    newVec.x = vec.x;
    newVec.y = vec.y;
    newVec.z = vec.z;
    return newVec;
}
//*/

glm::dvec3 ReactMath::rp3dVecToGlmD(reactphysics3d::Vector3 &vec) {
    glm::dvec3 newVec = {};
    newVec.x         = vec.x;
    newVec.y         = vec.y;
    newVec.z         = vec.z;
    return newVec;
}

/*
glm::mat4 rp3dMat4ToGlm(reactphysics3d::Transform& transform) {
    
    glm::mat4 newMat = {};
    newMat[0][0]     = transform[0][0];
    newMat[0][1];
    newMat[0][2];
    newMat[0][3];

    newMat[1][0] = transform[0][0];
    newMat[1][1];
    newMat[1][2];
    newMat[1][3];

    newMat[2][0] = transform[0][0];
    newMat[2][1];
    newMat[2][2];
    newMat[2][3];

    newMat[3][0] = transform[0][0];
    newMat[3][1];
    newMat[3][2];
    newMat[3][3];
}
*/
