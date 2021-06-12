//
// Created by charl on 19/05/2021.
//
#pragma once

#include "ReactShape.hpp"

class ReactSphereShape : public ReactShape{
public:
    /**
     * @brief Default Constructor
     */
    ReactSphereShape() =default;
    /**
     * @brief Default Destructor
     */
    ~ReactSphereShape() = default;
    /**
     * @brief Creates a sphere shape
     * @param radius
     * @param physicsCommon
     */
    void CreateSphereShape(float radius, reactphysics3d::PhysicsCommon &physicsCommon);
    /**
     * @brief Deletes a sphere shape
     * @param physicsCommon
     */
    void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) override;
private:
};
