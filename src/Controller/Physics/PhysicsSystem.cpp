//PhysicsSystem.cpp - manages physics

#include "PhysicsSystem.hpp"
#include "Controller/GameObjectManager.hpp"
#include <glm/gtx/string_cast.hpp>
#include "Controller/EventManager.hpp"
void PhysicsSystem::Init()
{
    // Create the world settings
    using reactphysics3d::DebugRenderer;
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    //settings.defaultVelocitySolverNbIterations = 20;
    //settings.isSleepingEnabled = false;
    settings.gravity = reactphysics3d::Vector3(0, -1, 0);

    physicsWorld = physicsCommon.createPhysicsWorld(settings);
    
    physicsWorld->setIsDebugRenderingEnabled(true);

    DebugRenderer& debugRenderer = physicsWorld->getDebugRenderer(); 

    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true); 
    path1 ="content/Shaders/ds.vert";
    path2 ="content/Shaders/fs.frag";
    shader_ = new Shader(path1.c_str(),path2.c_str());

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
}
void PhysicsSystem::DeInit()
{
    for(auto& collider : m_colliders)
    {
        collider.second.DeleteBody(physicsWorld,physicsCommon);
    }
    m_colliders.clear();
    physicsCommon.destroyPhysicsWorld(physicsWorld);
}

PhysicsSystem& PhysicsSystem::getInstance()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::update(float dt) const
{

    physicsWorld->update(static_cast<rp3d::decimal>(dt));

}

unsigned int PhysicsSystem::addSphere(unsigned int ID,Transform *transform, float radius)
{
    RigidBody object;
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
    RigidBody object;
    auto* shape = new ReactConcaveShape();
    glm::vec3 newPos = glm::vec3(transform->getPosition().x,transform->getPosition().y,transform->getPosition().z);
    object.CreateBody(ID,physicsWorld,newPos,transform->getRotation());
    shape->CreateConcaveShape(physicsCommon,modelID);
    object.AddCollisionShape(shape);
    object.SetBodyType(rp3d::BodyType::STATIC);
    unsigned int temp = object.getColliderID();
    m_colliders.emplace(object.getColliderID(),object);
    return temp;
}

unsigned int PhysicsSystem::addTerrainShape(unsigned int ID, Transform* transform,std::vector<std::vector<float>> heightvals)
{
    RigidBody terrain;
    ReactTerrainShape* terrShape = new ReactTerrainShape();
    glm::vec3 position(50, 123,50);
    auto orientation = glm::identity<glm::quat>();
    terrain.CreateBody(-2,physicsWorld,position,orientation);
    terrShape->CreateTerrainShape(physicsCommon,heightvals);
    terrain.AddCollisionShape(terrShape);
    terrain.SetBounciness(0.0);
    terrain.SetRollingResistance(1.0);
    terrain.SetBodyType(rp3d::BodyType::STATIC);
    unsigned int temp = terrain.getColliderID();
    m_colliders.emplace(terrain.getColliderID(),terrain);
    return temp;
}

unsigned int PhysicsSystem::addAABB(unsigned int ID,Transform* transform, float width, float height, float length)
{
    RigidBody object;
    auto* box = new ReactBoxShape();
    glm::vec3 newPos = glm::vec3(transform->getPosition().x,transform->getPosition().y,transform->getPosition().z);
    object.CreateBody(ID,physicsWorld,newPos,transform->getRotation());
    box->CreateBoxShape(glm::vec3(width,height,length),physicsCommon);
    object.AddCollisionShape(box);
    unsigned int temp = object.getColliderID();
    m_colliders.emplace(object.getColliderID(),object);

    return temp;
}

RigidBody * PhysicsSystem::getRigidBody(int colliderID)
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
        shader_->useShader();
        //TODO Setup the shader, verify data is okay being passed in like this.
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader_->setMat4("projection", EMS::getInstance().fire(ReturnMat4Event::getPerspective));
        shader_->setMat4("view", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
        shader_->setMat4("model", EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
//        const glm::mat4 localToCameraMatrix = view;
//        const glm::mat4 normalMatrix = glm::transpose(glm::inverse(localToCameraMatrix));
//        shader_->SetMat4("normalMatrix", normalMatrix);
//
//        // Set the model to camera matrix
//        shader_->SetMat4("localToWorldMatrix", glm::mat4());
//        shader_->SetMat4("worldToCameraMatrix", view);
//        shader_->SetBool("isGlobalVertexColorEnabled", false);
        // Lines
        if (line_num_ > 0) {
            // Bind the VAO
            glBindVertexArray(l_vao_);
            glBindBuffer(GL_ARRAY_BUFFER, l_vbo_);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);
            // Draw the lines geometry
            glDrawArrays(GL_LINES, 0, line_num_ * 2);

            glDisableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        if (triag_num_ > 0) {

            // Bind the VAO
            glBindVertexArray(t_vao_);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo_);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*) nullptr);

            // Draw the triangles geometry
            glDrawArrays(GL_TRIANGLES, 0, triag_num_ * 3);

            glDisableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //shader->Use();
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