#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"
//#include "ResolutionFunctions.hpp"

class PhysicsResolution : public rp3d::EventListener {
  public:

      virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;
      //virtual void onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData) override;

  private:
      void collisionResolution(int body1, int body2, double pen, glm::dvec3 contactNormal, glm::dvec3 body1ContactPoint, glm::dvec3 body2ContactPoint);
};