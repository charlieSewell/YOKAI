#pragma once

#include "Physics/PhysicsSystem.hpp"
#include "Engine/Component.hpp"
/**
 * @class RayCaster
 * @brief Casts rays for object picking
 */
class RayCaster : public Component, public rp3d::RaycastCallback {

public:
    /**
     * @brief Default constructor for the raycaster
     */
    RayCaster(GameObject* parent);
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
    /**
     * @brief Set the Own Collider ID
     * @param ownColliderID 
     */
    void SetOwnColliderID(int ownColliderID);
    /**
     * @brief Set the Excluded Collider ID
     * @param id 
     */
	void SetExcludedColliderID(int id);
    ///map of hits based on distance and colliderID
    std::map<rp3d::decimal,uint32_t> hits;
private:
    ///own collider ID
    unsigned int ownColliderID;
    ///other excluded collider ID
	unsigned int excludedColliderID = -1;
    
	
};


