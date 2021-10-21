#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"

class PhysicsResolution : public rp3d::EventListener {
  public:

      virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;
      //virtual void onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData) override;

  private:
      void collisionResolution(int body1, int body2, float pen, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint);
};