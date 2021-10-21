#pragma once

#include "Engine/ModelManager.hpp"
#include "Transform.hpp"
#include "DrawableEntity.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
/**
 * @class ConcaveCollider
 * @brief A concave bounding volume 
 */
class YOKAI_API ConcaveCollider : public Component {
    public: 
        /**
         * @brief Construct a new Concave Collider object
         * @param parent 
         */
        ConcaveCollider(GameObject* parent);
        /**
         * @brief Runs once when scene is ready to go
         */
        void Awake();
        /**
         * @brief Runs once a frame to update object
         * @param deltaTime 
         */
        void Update(float deltaTime);
    private:
        ///Collider ID
        unsigned int m_colliderID;
        ///Model ID
        unsigned int modelID;
};