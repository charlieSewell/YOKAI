//
// Created by charl on 20/05/2021.
//
#include "Controller/Physics/PhysicsSystem.hpp"
#pragma once
/**
 * @class RayCaster
 * @brief Casts rays for object picking
 */
class RayCaster : public rp3d::RaycastCallback {

public:
    /**
     * @brief Default constructor for the raycaster
     */
    RayCaster() = default;
    /**
     * @brief Casts a ray between 2 points and returns an object ID if hit else returns -1
     * @param startPosition
     * @param direction
     * @param distance
     * @return objID
     */
	int CastRay(glm::vec3 startPosition, glm::vec3 direction, float distance);
    /**
     * @brief Checks raycast data to see what was hit
     * @param info
     * @return
     */
    rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo &info) override;
    /// Sets own collider to be excluded
    void setOwnColliderID(int ownColliderID);
    /// Sets another collider to be excluded
	void setExcludedColliderID(int id);
    ///own collider ID
    unsigned int ownColliderID;
    ///other excluded collider ID
	unsigned int excludedColliderID = -1;
    ///map of hits based on distance and colliderID
	std::map<rp3d::decimal,uint32_t> hits;
};


