//
// Created by charl on 19/05/2021.
//
#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "Transform.hpp"
class ReactShape {
    public:
    /**
     * @brief Default Constructor
     */
    ReactShape() = default;
    /**
     * @brief Returns a pointer to the collision shape
     * @return CollisionShape*
     */
    virtual reactphysics3d::CollisionShape* getCollisionShape(){return m_shape;}
    /**
     * @brief Virtual function to delete a shape
     * @param physicsCommon
     */
    virtual void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon);
    /**
     * @brief Returns a shapeID
     * @return shapeID
     */
    unsigned int getShapeID() const{return m_shapeID;}
    /**
     * @brief Returns a pointer to the collision shape
     * @return CollisionShape*
     */
    reactphysics3d::CollisionShape *getShape();

protected:
    ///Shape Pointer
    reactphysics3d::CollisionShape* m_shape;
    ///ShapeID
    unsigned int m_shapeID;
};
