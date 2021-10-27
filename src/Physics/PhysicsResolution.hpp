#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"

class PhysicsResolution : public rp3d::EventListener {
  public:
      virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;

  private:
      void ResolvePenetration(int body1, int body2, float penetration, glm::vec3 contactNormal);
      void CollisionResolution(int body1, int body2, float penetration, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint, CollisionCallback::ContactPair::EventType eventType);
      glm::vec3 Damping(glm::vec3 vel);
};