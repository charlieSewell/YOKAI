#pragma once

#include <vector>
#include <map>
#include "CollisionBody.hpp"
#include "Components/Transform.hpp"
#include "ReactMath.hpp"
#include "Physics/Shapes/ReactTerrainShape.hpp"
#include "Physics/Shapes/ReactSphereShape.hpp"
#include "Physics/Shapes/ReactBoxShape.hpp"
#include "Physics/Shapes/ReactConcaveShape.hpp"
#include "Export.hpp"
//#include "PhysicsListener.hpp"
//#include "PhysicsResolution.hpp"
/**
 * @class PhysicsSystem
 * @brief Singleton that Manages physics
 */
class YOKAI_API PhysicsSystem
{
public:
    /**
     * @brief Returns this instance of Physics manager
     * @return PhysicsSystem&
     */
    static PhysicsSystem& getInstance();

    /**
     * @brief Initialises Physics Manager
     */
    void Init();

    ///Deleted copy constructor
    PhysicsSystem(PhysicsSystem const&) = delete;

    ///Deleted = operator
    void operator=(PhysicsSystem const&) = delete;
    /**
     * @brief Updates the simulation
     * @param float - dt
     */
    void update(float dt);


    // easy to implement if needed
    //int addBoundingSphere(glm::vec3 *position, double radius);
    /**
     * @brief Adds a bounding box
     * @param unsigned int - ID
     * @param Transform* - transform
     * @param float - width
     * @param float - length
     * @param float - height
     * @return ReactBoxShape*
     */
    unsigned int addAABB(unsigned int ID, Transform* transform, float width, float height, float length);
    /**
     * @brief Returns a collider given an ID
     * @param int - colliderID
     * @return RigidBody
     */

    CollisionBody * getPhysicsBody(int colliderID);
    /**
     * @brief Deletes a rigid Body
     * @param int - ID
     */
    void deleteRigidBody(int ID);
    /**
     * @brief Adds a sphere body to the scene
     * @param ID
     * @param transform
     * @param radius
     * @return unsigned int bodyID
     */
    unsigned int addSphere(unsigned int ID, Transform* transform,float radius);
    /**
     * @brief Adds a Concave body to the scene
     * @param ID 
     * @param transform 
     * @param modelID 
     * @return unsigned int 
     */
    unsigned int addConcaveShape(unsigned int ID, Transform* transform,unsigned int modelID);
    /**
     * @brief Adds a Terrain body to the scene
     * @param ID 
     * @param transform 
     * @param heightvals 
     * @return unsigned int 
     */
    unsigned int addTerrainShape(unsigned int ID, Transform* transform,std::vector<std::vector<float>> heightvals);
    /**
     * @brief Updates The debug renderer
     */
    void RendererUpdate();
    /**
     * @brief Draws the wireframe debug view
     */
    void Draw();
    /**
     * @brief DeInitialises the physics simulation
     */
    void DeInit();
    ///object to create physics shapes
    reactphysics3d::PhysicsCommon physicsCommon;
    ///physics world for simulation
    reactphysics3d::PhysicsWorld* physicsWorld;

    void TogglePhysicsDebug(){isDebugEnabled = !isDebugEnabled;}

    //Physics
    void IntegrateVelocities();

    void ClearColliders();

private:
    bool isDebugEnabled = false;
    ///Privatised Constructor
    PhysicsSystem() = default;
    std::string path1;
    std::string path2;
    ///Privatised destructor
    //Test Renderer Values
    unsigned int l_vbo_ = 0, l_vao_ = 0;
    unsigned int t_vbo_ = 0, t_vao_ = 0;
    unsigned int line_num_ = 0, triag_num_ = 0;
    /// The shared pointer to draw react objects,
    Shader* shader_ = nullptr;
    ///count of map
    int m_mapCount;
    ///map of colliders
    std::map<int, CollisionBody> m_colliders;	//TODO: make colliders so can add spheres
    glm::vec3 m_gravity;
};