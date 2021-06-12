//
// Created by Charlie Sewell on 13/05/2021.
//
#pragma once
#include "Controller/Factory/TerrainFactory.hpp"
#include "ReactShape.hpp"

class ReactTerrainShape : public ReactShape{
  public:
    /**
     * @brief Default Constructor
     */
    ReactTerrainShape();
    /**
     * @brief Default Destructor
     */
    ~ReactTerrainShape();
    /**
     * @brief Creates a Terrain Shape
     * @param physicsCommon
     */
    void CreateTerrainShape(reactphysics3d::PhysicsCommon &physicsCommon);
    /**
     * @brief Deletes a Terrain Shape
     * @param physicsCommon
     */
    void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) override;
  private:
    ///float* to heightfield array
    float *heightFieldArray;
};
