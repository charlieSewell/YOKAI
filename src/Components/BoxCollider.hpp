#pragma once
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
/**
 * @class BoxCollider
 * @brief Box collider component
 */
class YOKAI_API BoxCollider : public Component {
public:
    /**
     * @brief Construct a new Box Collider object
     * @param parent 
     */
    BoxCollider(GameObject* parent);
    /**
     * @brief Runs once when the scene is ready to go
     */
    void Awake();
    /**
     * @brief Updates Once a frame
     * @param deltaTime 
     */
    void Update(float deltaTime);
    /**
     * @brief Set the Extents of the Bounding Box
     * @param extent 
     */
    void SetExtents(glm::vec3 extent);
    /**
     * @brief Set the Extents of the Bounding Box
     * @param x 
     * @param y 
     * @param z 
     */
    void SetExtents(float x, float y, float z);
    /**
     * @brief Set the Orientation of the Bounding Box
     * @param orientation 
     */
	void SetOrientation(glm::quat orientation);
	/**
	* @brief Set the Positin of the Bounding Box
	* @param orientation
	*/
	void SetPosition(glm::vec3 newPosition);
private:
    ///Collider ID
    unsigned int m_colliderID;
    ///Extents of Bounding Box
    glm::vec3 extents;
};
