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
    void Update(float dt);
    /**
     * @brief Adds a bounding box
     * @param unsigned int - ID
     * @param Transform* - transform
     * @param float - width
     * @param float - length
     * @param float - height
     * @return ReactBoxShape*
     */
    unsigned int AddAABB(unsigned int ID, Transform* transform, float width, float height, float length);
    /**
     * @brief Returns a collider given an ID
     * @param int - colliderID
     * @return RigidBody
     */
    CollisionBody * GetPhysicsBody(int colliderID);
    /**
     * @brief Deletes a rigid Body
     * @param int - ID
     */
    void DeleteRigidBody(int ID);
    /**
     * @brief Adds a sphere body to the scene
     * @param ID
     * @param transform
     * @param radius
     * @return unsigned int bodyID
     */
    unsigned int AddSphere(unsigned int ID, Transform* transform,float radius);
    /**
     * @brief Adds a Concave body to the scene
     * @param ID 
     * @param transform 
     * @param modelID 
     * @return unsigned int 
     */
    unsigned int AddConcaveShape(unsigned int ID, Transform* transform,unsigned int modelID);
    /**
     * @brief Adds a Terrain body to the scene
     * @param ID 
     * @param transform 
     * @param heightvals 
     * @return unsigned int 
     */
    unsigned int AddTerrainShape(unsigned int ID, Transform* transform,std::vector<std::vector<float>> heightvals);
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
    /**
     * @brief Togles Debug Renderer
     */
    void TogglePhysicsDebug(){m_isDebugEnabled = !m_isDebugEnabled;}
    /**
     * @brief Intergrates Velocitys into bodys
     */
    void IntegrateVelocities();
    /**
     * @brief Clears all Colliders from world
     */
    void ClearColliders();
    /**
     * @brief Get the Physics World
     * @return reactphysics3d::PhysicsWorld* 
     */
    reactphysics3d::PhysicsWorld* GetPhysicsWorld(){return m_physicsWorld;}
    /**
     * @brief Get the Physics Common
     * @return reactphysics3d::PhysicsCommon* 
     */
    reactphysics3d::PhysicsCommon* GetPhysicsCommon(){return &m_physicsCommon;}
private:
    ///Privatised Constructor
    PhysicsSystem() = default;
    ///object to create physics shapes
    reactphysics3d::PhysicsCommon m_physicsCommon;
    ///physics world for simulation
    reactphysics3d::PhysicsWorld* m_physicsWorld;
    bool m_isDebugEnabled = false;
    ///path of vertex shader
    std::string m_vertexPath;
    ///path of fragment shader
    std::string m_fragmentPath;
    unsigned int l_vbo_ = 0, l_vao_ = 0;
    unsigned int t_vbo_ = 0, t_vao_ = 0;
    ///Line count for Debug Renderer
    unsigned int m_lineCount = 0;
    ///Triangle count for Debug Renderer
    unsigned int m_triangleCount = 0;
    /// The shared pointer to draw react objects,
    Shader* m_debugShader = nullptr;
    ///count of map
    int m_mapCount;
    ///map of colliders
    std::map<int, CollisionBody> m_colliders;	//TODO: make colliders so can add spheres
    ///Gravity of world
    glm::vec3 m_gravity;
};