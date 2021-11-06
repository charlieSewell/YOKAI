#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"
/**
 * @class PhysicsResolution
 * @brief Resolves collisions for objects in physics world
 */
class PhysicsResolution : public rp3d::EventListener {
  public:
    /**
     * @brief Called each physics update and gives contact data
     * @param callbackData 
     */
    virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;

  private:
    /**
     * @brief Resolves Penetration between 2 bodies
     * @param body1 
     * @param body2 
     * @param penetration 
     * @param contactNormal 
     */
    void ResolvePenetration(int body1, int body2, float penetration, glm::vec3 contactNormal);
    /**
     * @brief Resolves Collision between 2 bodies
     * 
     * @param body1 
     * @param body2 
     * @param penetration 
     * @param contactNormal 
     * @param body1ContactPoint 
     * @param body2ContactPoint 
     * @param eventType 
     */
    void CollisionResolution(int body1, int body2, float penetration, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint, CollisionCallback::ContactPair::EventType eventType);
};