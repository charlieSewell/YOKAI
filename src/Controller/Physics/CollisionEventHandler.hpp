//
// Created by Charlie Sewell on 13/05/2021.
//
#pragma once
#include <reactphysics3d/reactphysics3d.h>
/**
 * @class CollisionEventHandler
 * @brief Handles terrain collision events
 */
class CollisionEventHandler : public reactphysics3d::EventListener {
  public:
    /**
     * @brief Collision Event Handler Constructor
     */
    CollisionEventHandler() = default;
    /**
     * @brief collision contact callback
     * @param callbackData - callbackData
     */
    void onContact(const reactphysics3d::CollisionCallback::CallbackData &callbackData) override;
    //std::vector<std::pair<int,int>> collisions;
};

