//PhysicsSystem.cpp - manages physics

#include "PhysicsSystem.hpp"
#include "Engine/GameObjectManager.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/EventManager.hpp"
void PhysicsSystem::Init()
{
    // Create the world settings
    using reactphysics3d::DebugRenderer;
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    //settings.defaultVelocitySolverNbIterations = 20;
    //settings.isSleepingEnabled = false;
    settings.gravity = reactphysics3d::Vector3(0, 0, 0);

    m_physicsWorld = m_physicsCommon.createPhysicsWorld(settings);
    
    m_physicsWorld->setIsDebugRenderingEnabled(true);
    m_gravity = glm::vec3(0, -3, 0);

    DebugRenderer& debugRenderer = m_physicsWorld->getDebugRenderer(); 

    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true); 
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_POINT, true);
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_NORMAL, true);
    m_vertexPath ="content/Shaders/debugVertex.vs";
    m_fragmentPath ="content/Shaders/debugFragment.fs";
    m_debugShader = new Shader("content/Shaders/debugVertex.vert","content/Shaders/debugFragment.frag");

    //Generate line buffers for test renderer
    glGenVertexArrays(1, &l_vao_);
    assert(l_vao_ != 0);
    glGenBuffers(1, &l_vbo_);
    assert(l_vbo_ != 0);


    //Generate triangle buffers for test renderer
    glGenVertexArrays(1, &t_vao_);
    assert(t_vao_ != 0);
    glGenBuffers(1, &t_vbo_);
    assert(t_vbo_ != 0);
}
void PhysicsSystem::DeInit()
{
    for(auto& m_collider : m_colliders)
    {
        m_collider.second.DeleteBody(m_physicsWorld,m_physicsCommon);
    }
    m_colliders.clear();
    m_physicsCommon.destroyPhysicsWorld(m_physicsWorld);
}
void PhysicsSystem::ClearColliders()
{
    for(auto& m_collider : m_colliders)
    {
        m_collider.second.DeleteBody(m_physicsWorld,m_physicsCommon);
    }
    m_colliders.clear();
}
PhysicsSystem& PhysicsSystem::getInstance()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::Update(float dt)
{
    
    m_physicsWorld->update(static_cast<rp3d::decimal>(dt));
	
    //Intergrate Gravity
    for (auto &m_collider : m_colliders) 
    {
        if (m_collider.second.GetGravityAffected()) 
        {
             m_collider.second.SetLinearVelocity(m_collider.second.GetLinearVelocity() + (dt * m_gravity));
        }
    }
    //Intergrate Positions
    for (auto &m_collider : m_colliders) 
    {
        if (!m_collider.second.GetIsStaticObject()) 
        {
            m_collider.second.SetPosition(m_collider.second.GetPosition() + m_collider.second.GetLinearVelocity() * dt);
            m_collider.second.SetOrientation(glm::normalize(m_collider.second.GetOrientation() + ((0.5f * glm::quat(0.0, m_collider.second.GetAngularVelocity()) * m_collider.second.GetOrientation())*dt)));
            m_collider.second.SetCentreOfMass(m_collider.second.GetPosition());

            m_collider.second.UpdateBody();
        }
    }

}

unsigned int PhysicsSystem::AddSphere(unsigned int ID,Transform *transform, float radius)
{
    CollisionBody object;
    auto* sphere = new ReactSphereShape();
    object.CreateBody(ID,m_physicsWorld,transform->GetPosition(),transform->GetRotation());
    sphere->CreateSphereShape(radius,m_physicsCommon);
    object.AddCollisionShape(sphere);
    unsigned int temp = object.GetColliderID();
    m_colliders.emplace(object.GetColliderID(),object);
    return temp;
}

unsigned int PhysicsSystem::AddConcaveShape(unsigned int ID, Transform* transform,unsigned int modelID)
{
    CollisionBody object;
    auto* shape = new ReactConcaveShape();
    glm::vec3 newPos = glm::vec3(transform->GetPosition().x,transform->GetPosition().y,transform->GetPosition().z);
    object.CreateBody(ID,m_physicsWorld,newPos,transform->GetRotation());
    shape->CreateConcaveShape(m_physicsCommon,modelID);
    object.AddCollisionShape(shape);
    unsigned int temp = object.GetColliderID();
    m_colliders.emplace(object.GetColliderID(),object);
    return temp;
}

unsigned int PhysicsSystem::AddTerrainShape(unsigned int ID, Transform* transform,std::vector<std::vector<float>> heightvals)
{
    CollisionBody terrain;
    ReactTerrainShape* terrShape = new ReactTerrainShape();
    glm::vec3 position = transform->GetPosition();
    auto orientation = glm::identity<glm::quat>();
    terrain.CreateBody(ID,m_physicsWorld,position,orientation);
    terrShape->CreateTerrainShape(m_physicsCommon,heightvals);
    terrain.AddCollisionShape(terrShape);
    terrain.SetRollingResistance(1.0);
    unsigned int temp = terrain.GetColliderID();
    m_colliders.emplace(terrain.GetColliderID(),terrain);
    return temp;
}

unsigned int PhysicsSystem::AddAABB(unsigned int ID,Transform* transform, float width, float height, float length)
{
    CollisionBody object;
    auto* box = new ReactBoxShape();
    glm::vec3 newPos = glm::vec3(transform->GetPosition().x,transform->GetPosition().y,transform->GetPosition().z);
    object.CreateBody(ID,m_physicsWorld,newPos,transform->GetRotation());
    box->CreateBoxShape(glm::vec3(width,height,length),m_physicsCommon);
    object.AddCollisionShape(box);
    unsigned int temp = object.GetColliderID();
    m_colliders.emplace(object.GetColliderID(),object);
    return temp;
}

CollisionBody * PhysicsSystem::GetPhysicsBody(int colliderID)
{
    try{
        return &m_colliders.at(colliderID);
    } catch (std::exception &e) {
        std::cout << colliderID <<std::endl;
        std::cout << e.what() <<std::endl;
        return nullptr;
    }
}

void PhysicsSystem::DeleteRigidBody(int ID)
{
    m_colliders.at(ID).DeleteBody(m_physicsWorld,m_physicsCommon);
    m_colliders.erase(ID);
}

void PhysicsSystem::Draw()
 {
     if(m_isDebugEnabled)
     {
        m_debugShader->UseShader();
        //TODO Setup the shader, verify data is okay being passed in like this.
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_debugShader->SetMat4("projection", EMS::getInstance().fire(ReturnMat4Event::getPerspective));
        m_debugShader->SetMat4("view", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
        m_debugShader->SetMat4("model", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));

        glBindVertexArray(l_vao_);
        glBindBuffer(GL_ARRAY_BUFFER, l_vbo_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);
            
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*) sizeof(rp3d::Vector3));
            
        // Draw the lines geometry
        glDrawArrays(GL_LINES, 0, m_lineCount * 2);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Bind the VAO
        glBindVertexArray(t_vao_);
        glBindBuffer(GL_ARRAY_BUFFER, t_vbo_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*) sizeof(rp3d::Vector3));
        // Draw the triangles geometry
        glDrawArrays(GL_TRIANGLES, 0, m_triangleCount * 3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //shader->Use();
     }
}

void PhysicsSystem::RendererUpdate() {
    reactphysics3d::DebugRenderer& debug_renderer = m_physicsWorld->getDebugRenderer();
    if(Yokai::getInstance().GetIsPaused())
    {
        debug_renderer.reset();
        debug_renderer.computeDebugRenderingPrimitives(*m_physicsWorld);
    }
    
    m_lineCount = debug_renderer.getNbLines();
    if (m_lineCount > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, l_vbo_);
        auto sizeVertices = static_cast<GLsizei>(m_lineCount * sizeof(rp3d::DebugRenderer::DebugLine));
        glBufferData(GL_ARRAY_BUFFER, sizeVertices, debug_renderer.getLinesArray(), GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    m_triangleCount = debug_renderer.getNbTriangles();
    if (m_triangleCount > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, t_vbo_);
        auto sizeVertices = static_cast<GLsizei>(m_triangleCount * sizeof(rp3d::DebugRenderer::DebugTriangle));
        glBufferData(GL_ARRAY_BUFFER, sizeVertices, debug_renderer.getTrianglesArray(), GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}