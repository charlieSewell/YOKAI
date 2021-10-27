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

    physicsWorld = physicsCommon.createPhysicsWorld(settings);
    
    physicsWorld->setIsDebugRenderingEnabled(true);
    //physicsWorld->setEventListener(listener.getListener());

    DebugRenderer& debugRenderer = physicsWorld->getDebugRenderer(); 

    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true); 
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_POINT, true);
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_NORMAL, true);
    path1 ="content/Shaders/debugVertex.vs";
    path2 ="content/Shaders/debugFragment.fs";
    shader_ = new Shader("content/Shaders/debugVertex.vert","content/Shaders/debugFragment.frag");

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


    //physicsWorld->setEventListener(&listener);
    //for (auto &n : m_colliders) {
    //    n.second.SetMass(10);
    //}
}
void PhysicsSystem::DeInit()
{
    for(auto& m_collider : m_colliders)
    {
        m_collider.second.DeleteBody(physicsWorld,physicsCommon);
    }
    m_colliders.clear();
    physicsCommon.destroyPhysicsWorld(physicsWorld);
}

PhysicsSystem& PhysicsSystem::getInstance()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::update(float dt)
{

    physicsWorld->update(static_cast<rp3d::decimal>(dt));
	
     for (auto &m_collider : m_colliders) {
        if (m_collider.second.GetGravityAffected()) {
             m_collider.second.SetLinearVelocity(m_collider.second.GetLinearVelocity() +(dt * glm::vec3(0, -1, 0)));
            // std::cout << (glm::dvec3(0, -1, 0) * double(dt)).x << ", " << (glm::dvec3(0, -1, 0) *
            // double(dt)).y << ", " << (glm::dvec3(0, -1, 0) * double(dt)).z << std::endl;
        }
    }

    for (auto &m_collider : m_colliders) {
        if (!m_collider.second.GetIsStaticObject()) 
        {
            m_collider.second.SetPosition(m_collider.second.GetPosition() + m_collider.second.GetLinearVelocity() * dt);
            m_collider.second.SetOrientation(glm::normalize(m_collider.second.GetOrientation() + ((0.5f * glm::quat(0.0, m_collider.second.GetAngularVelocity()) * m_collider.second.GetOrientation())*dt)));
            m_collider.second.SetCentreOfMass(m_collider.second.GetPosition());

            m_collider.second.UpdateBody();
        }
    }

	m_linearVelocities.clear();
    m_angularVelocities.clear();
}

unsigned int PhysicsSystem::addSphere(unsigned int ID,Transform *transform, float radius)
{
    CollisionBody object;
    auto* sphere = new ReactSphereShape();
    object.CreateBody(ID,physicsWorld,transform->getPosition(),transform->getRotation());
    sphere->CreateSphereShape(radius,physicsCommon);
    object.AddCollisionShape(sphere);
    unsigned int temp = object.getColliderID();
    m_colliders.emplace(object.getColliderID(),object);
    return temp;
}

unsigned int PhysicsSystem::addConcaveShape(unsigned int ID, Transform* transform,unsigned int modelID)
{
    CollisionBody object;
    auto* shape = new ReactConcaveShape();
    glm::vec3 newPos = glm::vec3(transform->getPosition().x,transform->getPosition().y,transform->getPosition().z);
    object.CreateBody(ID,physicsWorld,newPos,transform->getRotation());
    shape->CreateConcaveShape(physicsCommon,modelID);
    object.AddCollisionShape(shape);
    unsigned int temp = object.getColliderID();
    m_colliders.emplace(object.getColliderID(),object);
    return temp;
}

unsigned int PhysicsSystem::addTerrainShape(unsigned int ID, Transform* transform,std::vector<std::vector<float>> heightvals)
{
    CollisionBody terrain;
    ReactTerrainShape* terrShape = new ReactTerrainShape();
    glm::vec3 position = transform->getPosition();
    auto orientation = glm::identity<glm::quat>();
    terrain.CreateBody(ID,physicsWorld,position,orientation);
    terrShape->CreateTerrainShape(physicsCommon,heightvals);
    terrain.AddCollisionShape(terrShape);
    terrain.SetRollingResistance(1.0);
    unsigned int temp = terrain.getColliderID();
    m_colliders.emplace(terrain.getColliderID(),terrain);
    return temp;
}

unsigned int PhysicsSystem::addAABB(unsigned int ID,Transform* transform, float width, float height, float length)
{
    CollisionBody object;
    auto* box = new ReactBoxShape();
    glm::vec3 newPos = glm::vec3(transform->getPosition().x,transform->getPosition().y,transform->getPosition().z);
    object.CreateBody(ID,physicsWorld,newPos,transform->getRotation());
    box->CreateBoxShape(glm::vec3(width,height,length),physicsCommon);
    object.AddCollisionShape(box);
    unsigned int temp = object.getColliderID();
    m_colliders.emplace(object.getColliderID(),object);
    return temp;
}

CollisionBody * PhysicsSystem::getPhysicsBody(int colliderID)
{
    try{
        return &m_colliders.at(colliderID);
    } catch (std::exception &e) {
        std::cout << colliderID <<std::endl;
        std::cout << e.what() <<std::endl;
        return nullptr;
    }
}

void PhysicsSystem::deleteRigidBody(int ID)
{
    m_colliders.at(ID).DeleteBody(physicsWorld,physicsCommon);
    m_colliders.erase(ID);
}

void PhysicsSystem::Draw()
 {
     if(isDebugEnabled)
     {
        shader_->useShader();
        //TODO Setup the shader, verify data is okay being passed in like this.
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader_->setMat4("projection", EMS::getInstance().fire(ReturnMat4Event::getPerspective));
        shader_->setMat4("view", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
        shader_->setMat4("model", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));

        if (line_num_ > 0) {
            // Bind the VAO
            glBindVertexArray(l_vao_);
            glBindBuffer(GL_ARRAY_BUFFER, l_vbo_);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);
            
            glEnableVertexAttribArray(1);
            glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*) sizeof(rp3d::Vector3));
            
            // Draw the lines geometry
            glDrawArrays(GL_LINES, 0, line_num_ * 2);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        if (triag_num_ > 0) {

            // Bind the VAO
            glBindVertexArray(t_vao_);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo_);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);

            glEnableVertexAttribArray(1);
            glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*) sizeof(rp3d::Vector3));

            // Draw the triangles geometry
            glDrawArrays(GL_TRIANGLES, 0, triag_num_ * 3);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //shader->Use();
     }
}

void PhysicsSystem::RendererUpdate() {
    reactphysics3d::DebugRenderer& debug_renderer = physicsWorld->getDebugRenderer();
    line_num_ = debug_renderer.getNbLines();
    if (line_num_ > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, l_vbo_);
        auto sizeVertices = static_cast<GLsizei>(line_num_ * sizeof(rp3d::DebugRenderer::DebugLine));
        glBufferData(GL_ARRAY_BUFFER, sizeVertices, debug_renderer.getLinesArray(), GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    triag_num_ = debug_renderer.getNbTriangles();
    if (triag_num_ > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, t_vbo_);
        auto sizeVertices = static_cast<GLsizei>(triag_num_ * sizeof(rp3d::DebugRenderer::DebugTriangle));
        glBufferData(GL_ARRAY_BUFFER, sizeVertices, debug_renderer.getTrianglesArray(), GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void PhysicsSystem::SubmitLinearVelocity(int colliderID, glm::dvec3 linearVelocity)
{
	if(m_linearVelocities.find(colliderID) == m_linearVelocities.end())
	{
		m_linearVelocities[colliderID] = std::pair<glm::dvec3, int>(linearVelocity, 1);
	}
	else
	{
		m_linearVelocities[colliderID].first += linearVelocity;
		m_linearVelocities[colliderID].second++;
	}
}

void PhysicsSystem::SubmitAngularVelocity(int colliderID, glm::dvec3 angularVelocity) 
{
    if (m_angularVelocities.find(colliderID) == m_angularVelocities.end()) 
    {
        m_angularVelocities[colliderID] = std::pair<glm::dvec3, int>(angularVelocity, 1);
    } 
    else 
    {
        m_angularVelocities[colliderID].first += angularVelocity;
        m_angularVelocities[colliderID].second++;
    }
}