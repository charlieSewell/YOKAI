#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "ReactMath.hpp"
#include "PhysicsSystem.hpp"

class PhysicsResolution : public rp3d::EventListener {
  public:

      virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;

      //virtual void onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData) override;

};