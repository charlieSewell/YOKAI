#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"

class PhysicsResolution : public rp3d::EventListener {
  public:
      virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;

  private:
      void ResolvePenetration(int body1, int body2, double penetration, glm::dvec3 contactNormal);
      void CollisionResolution(int body1, int body2, glm::dvec3 contactNormal, glm::dvec3 body1ContactPoint, glm::dvec3 body2ContactPoint);
};