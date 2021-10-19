#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>

class PhysicsResolution : public rp3d::EventListener {
  public:
    virtual void onContact(const rp3d::CollisionCallback::CallbackData &callbackData) override;
};